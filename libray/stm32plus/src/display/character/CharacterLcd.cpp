/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "display/character/CharacterLcd.h"

namespace stm32plus {
    namespace display {

        /**
         * Write a string of characters to the display. This convenience goes into a loop
         * and calls write().
         *
         * @param str_ The null terminated string to write.
         * @see write
         */

        void CharacterLcd::writeString(const char *str_) {

            while(*str_)
                write(*str_++);
        }
    }
}

