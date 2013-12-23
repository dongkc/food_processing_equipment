/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include <stdint.h>
#include "display/graphic/FontChar.h"


namespace stm32plus {
    namespace display {

        /**
         * Implementation of a font compiled into memory
         */

        class Font {
            private:
                uint8_t _characterCount;
                uint8_t _height;
                uint8_t _characterSpacing;
                uint8_t _firstCharacter;
                const struct FontChar * _characters;

            public:
                Font(uint8_t firstChar,uint8_t characterCount,uint8_t height,uint8_t spacing,const struct FontChar *characters);

                void getCharacter(uint8_t character,const FontChar*& fc) const;
                uint16_t getId() const;
                uint8_t getHeight() const;
                uint8_t getCharacterSpacing() const;
        };
    }
}
