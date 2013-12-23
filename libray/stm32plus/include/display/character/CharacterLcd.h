/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#pragma once

#include <stdint.h>

namespace stm32plus {

    /**
     * The stm32plus::display namespace is a sub-namespace of stm32plus that contains all classes to do with LCDs, OLEDs etc.
     */

    namespace display {

        /**
         * Base class for character based LCD displays
         */

        class CharacterLcd {

            public:

                /**
                 * Possible display states
                 */

                enum DisplayState {
                    /// The display is currently on
                    DISPLAY_ON,
                    /// The display is currently off
                    DISPLAY_OFF
                };

                /**
                 * Possible cursor blink states
                 */

                enum BlinkState {
                    /// blinking is on
                    BLINK_ON,
                    /// blinking is off
                    BLINK_OFF
                };

                /**
                 * Possible cursor visibility states
                 */

                enum CursorState {
                    /// cursor is on
                    CURSOR_ON,
                    /// cursor is off
                    CURSOR_OFF
                };

                /**
                 * Possible scroll directions
                 */

                enum ScrollDirection {
                    /// scroll to the left
                    SCROLL_LEFT,
                    /// scroll to the right
                    SCROLL_RIGHT
                };

                /**
                 * Possible text output direction
                 */

                enum TextDirection {
                    /// left to right
                    TEXT_DIRECTION_LR,
                    /// right to left
                    TEXT_DIRECTION_RL
                };

                /**
                 * Possible auto-scroll states
                 */

                enum AutoScrollState {
                    /// auto scrolling is on
                    AUTO_SCROLL_ON,
                    /// auto scrolling is off
                    AUTO_SCROLL_OFF
                };

            public:
                virtual void writeString(const char *str_);

                /**
                 * Clear the screen
                 */

                virtual void clear()=0;

                /**
                 * Move the cursor to the given co-ords
                 * @param[in] x_ column address
                 * @param[in] y_ row address
                 */

                virtual void moveCursor(uint8_t x_,uint8_t y_)=0;

                /**
                 * Write a single character at the current cursor position
                 * @param[in] char_ the character to write
                 */

                virtual void write(uint8_t char_)=0;

                /**
                 * Change the display state
                 * @param[in] newState_ The new state of the display.
                 */

                virtual void setDisplay(DisplayState newState_)=0;

                /**
                 * Change the blink state
                 * @param[in] newState_ The new display state.
                 */

                virtual void setBlink(BlinkState newState_)=0;

                /**
                 * Set the cursor state
                 * @param[in] newState_ The new cursor state.
                 */

                virtual void setCursor(CursorState newState_)=0;

                /**
                 * Scroll the display
                 * @param[in] direction_ The new scroll direction.
                 */

                virtual void scrollDisplay(ScrollDirection direction_)=0;

                /**
                 * Set the text output direction
                 * @param[in] direction_ The new text direction.
                 */

                virtual void setTextDirection(TextDirection direction_)=0;

                /**
                 * Set the auto-scroll state
                 * @param[in] newState_ The new auto-scroll state
                 */

                virtual void setAutoScroll(AutoScrollState newState_)=0;

                /**
                 * Get the width of the display in characters
                 * @return The width.
                 */

                virtual uint16_t getWidth()=0;


                /**
                 * Get the height of the display in characters
                 * @return The height.
                 */

                virtual uint16_t getHeight()=0;
        };
    }
}
