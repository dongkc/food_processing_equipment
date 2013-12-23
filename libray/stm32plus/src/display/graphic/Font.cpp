/*
 * Font.cpp
 *
 *  Created on: 22 Apr 2012
 *      Author: Andy
 */

#include <cstdlib>
#include "display/graphic/Font.h"
#include "config/stdperiph.h"


namespace stm32plus {
    namespace display {

        /**
         * Constructor
         */

        Font::Font(uint8_t firstChar,uint8_t characterCount,uint8_t height,uint8_t spacing,const struct FontChar *characters) {

            _characterCount=characterCount;
            _firstCharacter=firstChar;
            _height=height;
            _characterSpacing=spacing;
            _characters=characters;
        }


        /**
         * Get the font character definition address
         */

        void Font::getCharacter(uint8_t character,const FontChar*& fc) const {

            const FontChar *ptr;
            int16_t i;

            // the bulk of the characters are in sequential order, see if we can
            // index directly into the character array to find it

            ptr=NULL;

            if(character-_firstCharacter<_characterCount) {

                if(_characters[character-_firstCharacter].Code==character)
                    ptr=&_characters[character-_firstCharacter];
                else {

                    // did't find it, search for it going backwards because the likelihood is that
                    // it's towards the end of the array

                    for(i=_characterCount-1;i>=0;i--) {

                        if(_characters[i].Code==character) {
                            ptr=&_characters[i];
                            break;
                        }
                    }
                }
            }

            if(ptr==NULL)
                ptr=&_characters[0];

            // set up the return data

            fc=ptr;
        }

        /**
         * Get the font height.
         */

        uint8_t Font::getHeight() const {
            return _height;
        }


        /**
         * Get the character spacing
         */

        uint8_t Font::getCharacterSpacing() const {
            return _characterSpacing;
        }
    }
}
