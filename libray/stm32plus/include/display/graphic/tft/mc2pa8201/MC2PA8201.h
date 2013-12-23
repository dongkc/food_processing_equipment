/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once


#include "display/graphic/Rectangle.h"
#include "display/graphic/PanelConfiguration.h"
#include "display/graphic/tft/mc2pa8201/MC2PA8201Colour.h"
#include "display/graphic/tft/mc2pa8201/MC2PA8201Orientation.h"
#include "display/graphic/tft/mc2pa8201/MC2PA8201Gamma.h"
#include "display/graphic/tft/mc2pa8201/commands/AllCommands.h"
#include "timing/MillisecondTimer.h"


namespace stm32plus {
    namespace display {

        /**
         * Generic MC2PA8201 template. The user can specialise based on the desired colour
         * depth, orientation and access mode.
         */

        template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
        class MC2PA8201 : public MC2PA8201Colour<TColourDepth,TAccessMode>,
                                            public MC2PA8201Orientation<TOrientation,TAccessMode> {

            public:
                enum {
                    SHORT_SIDE = 240,
                    LONG_SIDE = 320
                };

            protected:
                TAccessMode& _accessMode;

            public:
                MC2PA8201(TAccessMode& accessMode);

                void initialise() const;

                void applyGamma(MC2PA8201Gamma& gamma) const;
                void sleep() const;
                void wake() const;
                void beginWriting() const;
                void setScrollArea(uint16_t y,uint16_t height) const;

                DmaFsmcLcdMemoryCopy *createDmaMemoryCopy(DMA_Channel_TypeDef *channel) const;
        };


        /**
         * Constructor. Pass the access mode reference up the hierarchy where it'll get stored in the
         * common base class for use by all.
         */

        template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
        inline MC2PA8201<TOrientation,TColourDepth,TAccessMode>::MC2PA8201(TAccessMode& accessMode)
            : MC2PA8201Colour<TColourDepth,TAccessMode>(accessMode),
              MC2PA8201Orientation<TOrientation,TAccessMode>(accessMode),
              _accessMode(accessMode) {
        }


        /**
         * Initialise the LCD. Do the reset sequence.
         */

        template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
        inline void MC2PA8201<TOrientation,TColourDepth,TAccessMode>::initialise() const {

            // reset the device

            this->_accessMode.reset();

            // start up the display

            this->_accessMode.writeCommand(mc2pa8201::SLEEP_OUT);
            MillisecondTimer::delay(10);
            this->_accessMode.writeCommand(mc2pa8201::DISPLAY_INVERSION_OFF);
            this->_accessMode.writeCommand(mc2pa8201::IDLE_MODE_OFF);
            this->_accessMode.writeCommand(mc2pa8201::NORMAL_DISPLAY_MODE_ON);

            // interface pixel format comes from the colour specialisation

            this->_accessMode.writeCommand(mc2pa8201::INTERFACE_PIXEL_FORMAT,this->getInterfacePixelFormat());

            // memory access control comes from the orientation specialisation

            this->_accessMode.writeCommand(mc2pa8201::MEMORY_ACCESS_CONTROL,this->getMemoryAccessControl());

            // reset the scrolling area

            setScrollArea(0,320);

            // wait the required number of ms. before we can turn the display on

            MillisecondTimer::delay(125);
            this->_accessMode.writeCommand(mc2pa8201::DISPLAY_ON);
        }


        /**
         * Apply the panel gamma settings
         * @param gamma The gamma class containing the one value
         */

        template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
        inline void MC2PA8201<TOrientation,TColourDepth,TAccessMode>::applyGamma(MC2PA8201Gamma& gamma) const {

          this->_accessMode.writeCommand(mc2pa8201::GAMMA_SET,gamma[0] & 0xf);
        }


        /**
         * Send the panel to sleep
         */

        template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
        inline void MC2PA8201<TOrientation,TColourDepth,TAccessMode>::sleep() const {

            this->_accessMode.writeCommand(mc2pa8201::DISPLAY_OFF);
            this->_accessMode.writeCommand(mc2pa8201::SLEEP_IN);
            MillisecondTimer::delay(5);
        }


        /**
         * Wake the panel up
         */

        template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
        inline void MC2PA8201<TOrientation,TColourDepth,TAccessMode>::wake() const {

            this->_accessMode.writeCommand(mc2pa8201::SLEEP_OUT);
            MillisecondTimer::delay(120);
            this->_accessMode.writeCommand(mc2pa8201::DISPLAY_ON);
            MillisecondTimer::delay(5);
        }


        /**
         * Issue the command that allows graphics ram writing to commence
         */

        template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
        inline void MC2PA8201<TOrientation,TColourDepth,TAccessMode>::beginWriting() const {
          this->_accessMode.writeCommand(mc2pa8201::MEMORY_WRITE);
        }


        /**
         * Create a DMA memory copier
         */

        template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
        inline DmaFsmcLcdMemoryCopy *MC2PA8201<TOrientation,TColourDepth,TAccessMode>::createDmaMemoryCopy(DMA_Channel_TypeDef *channel) const {
            return this->_accessMode.createDmaMemoryCopy(channel);
        }


        /**
         * Set the scroll area to a full-width rectangle region
         * @param y The y-co-ord of the region
         * @param height The height of the region
         */

        template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
        inline void MC2PA8201<TOrientation,TColourDepth,TAccessMode>::setScrollArea(uint16_t y,uint16_t height) const {
            uint16_t bfa;

            bfa=320-height-y;

            this->_accessMode.writeCommand(mc2pa8201::VERTICAL_SCROLLING_DEFINITION);
            this->_accessMode.writeData(y >> 8);
            this->_accessMode.writeData(y & 0xff);
            this->_accessMode.writeData(height >> 8);
            this->_accessMode.writeData(height & 0xff);
            this->_accessMode.writeData(bfa >> 8);
            this->_accessMode.writeData(bfa & 0xff);
        }
    }
}
