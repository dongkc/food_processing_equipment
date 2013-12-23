/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "display/graphic/PanelConfiguration.h"
#include "display/graphic/Rectangle.h"
#include "display/graphic/tft/mc2pa8201/commands/AllCommands.h"


namespace stm32plus {
    namespace display {


        /**
         * Specialisation of MC2PA8201Orientation for the panel in LANDSCAPE mode.
         * @tparam TAccessMode the access mode implementation, e.g. FSMC
         */

        template<class TAccessMode>
        class MC2PA8201Orientation<LANDSCAPE,TAccessMode> {

            private:
                TAccessMode& _accessMode;

            protected:
                MC2PA8201Orientation(TAccessMode& accessMode);

                uint16_t getMemoryAccessControl() const;

          public:
                int16_t getWidth() const;
                int16_t getHeight() const;
                void moveTo(const Rectangle& rc) const;

                void setScrollPosition(int16_t scrollPosition);
        };


        /**
         * Constructor
         */

        template<class TAccessMode>
        inline MC2PA8201Orientation<LANDSCAPE,TAccessMode>::MC2PA8201Orientation(TAccessMode& accessMode)
            : _accessMode(accessMode) {
        }


        /**
         * Get the register setting for memory access control
         * @return The entry mode register setting for portrait
         */

        template<class TAccessMode>
        inline uint16_t MC2PA8201Orientation<LANDSCAPE,TAccessMode>::getMemoryAccessControl() const {
            return 0xa8;
        }


        /**
         * Get the width in pixels
         * @return 240px
         */

        template<class TAccessMode>
        inline int16_t MC2PA8201Orientation<LANDSCAPE,TAccessMode>::getWidth() const {
          return 320;
        }


        /**
         * Get the height in pixels
         * @return 320px
         */

        template<class TAccessMode>
        inline int16_t MC2PA8201Orientation<LANDSCAPE,TAccessMode>::getHeight() const {
          return 240;
        }


        /**
         * Move the display output rectangle
         * @param rc The display output rectangle
         */

        template<class TAccessMode>
        inline void MC2PA8201Orientation<LANDSCAPE,TAccessMode>::moveTo(const Rectangle& rc) const {

            this->_accessMode.writeCommand(mc2pa8201::COLUMN_ADDRESS_SET);

            this->_accessMode.writeData(rc.X >> 8);                    // x=0..319
            this->_accessMode.writeData(rc.X & 0xff);
            this->_accessMode.writeData((rc.X+rc.Width-1)>>8);
            this->_accessMode.writeData((rc.X+rc.Width-1) & 0xff);

            this->_accessMode.writeCommand(mc2pa8201::PAGE_ADDRESS_SET);

            this->_accessMode.writeData(0);                                // y=0..239
            this->_accessMode.writeData(rc.Y);
            this->_accessMode.writeData(0);
            this->_accessMode.writeData(rc.Y+rc.Height-1);
        }


        /**
         * Set a vertical scroll position
         * @param scrollPosition The new scroll position
         */

        template<class TAccessMode>
        inline void MC2PA8201Orientation<LANDSCAPE,TAccessMode>::setScrollPosition(int16_t scrollPosition) {

            // pull into range

            if(scrollPosition<0)
                scrollPosition+=320;
            else if(scrollPosition>319)
                scrollPosition-=320;

            // translate according to panel traits

            scrollPosition=scrollPosition ? 320-scrollPosition : 0;

            // write to the register

            this->_accessMode.writeCommand(mc2pa8201::VERTICAL_SCROLLING_START_ADDRESS);
            this->_accessMode.writeData(scrollPosition >> 8);
            this->_accessMode.writeData(scrollPosition & 0xff);
        }
    }
}

