/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "display/graphic/PanelConfiguration.h"
#include "display/graphic/Rectangle.h"


namespace stm32plus {
    namespace display {


        /**
         * Specialisation of SSD1306Orientation for the panel in PORTRAIT mode.
         * @tparam TAccessMode the access mode implementation, e.g. SPI
         */

        template<class TAccessMode>
        class SSD1306Orientation<PORTRAIT,TAccessMode> {

            private:
                TAccessMode& _accessMode;
                Point _cursorPos;
                Rectangle _window;

            protected:
                SSD1306Orientation(TAccessMode& accessMode);

                void setOrientation() const;

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
        inline SSD1306Orientation<PORTRAIT,TAccessMode>::SSD1306Orientation(TAccessMode& accessMode)
            : _accessMode(accessMode) {
        }


        /**
         * Set up for portrait mode
         */

        template<class TAccessMode>
        inline void SSD1306Orientation<PORTRAIT,TAccessMode>::setOrientation() const {
            this->_accessMode.writeCommand(0xA0);            // Set Segment Re-Map
        }


        /**
         * Get the width in pixels
         * @return 64
         */

        template<class TAccessMode>
        inline int16_t SSD1306Orientation<PORTRAIT,TAccessMode>::getWidth() const {
          return 64;
        }


        /**
         * Get the height in pixels
         * @return 128px
         */

        template<class TAccessMode>
        inline int16_t SSD1306Orientation<PORTRAIT,TAccessMode>::getHeight() const {
          return 128;
        }


        /**
         * Move the display output rectangle
         * @param rc The display output rectangle
         */

        template<class TAccessMode>
        inline void SSD1306Orientation<PORTRAIT,TAccessMode>::moveTo(const Rectangle& rc) const {

            _window.X=rc.Y;
            _window.Y=rc.X;
            _window.Width=rc.Height;
            _window.Height=rc.Width;

            _cursorPos=_window.getTopLeft();

            this->_accessMode.writeCommand(0x21);                // set column address
            this->_accessMode.writeCommand(rc.X / 8);
            this->_accessMode.writeCommand(rc.X+rc.Width-1);

            this->_accessMode.writeCommand(0x22);                // set page address (8 pages, 8 bits per page = 64 pixels)
            this->_accessMode.writeCommand(rc.Y);
            this->_accessMode.writeCommand(rc.Y+rc.Height-1);
        }


        /**
         * Set a vertical scroll position
         * @param scrollPosition The new scroll position
         */

        template<class TAccessMode>
        inline void SSD1306Orientation<PORTRAIT,TAccessMode>::setScrollPosition(int16_t scrollPosition) {
        }
    }
}

