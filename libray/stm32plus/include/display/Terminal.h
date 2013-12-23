/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "display/graphic/Point.h"
#include "display/graphic/Size.h"

namespace stm32plus {
    namespace display {

        /**
         * @brief Basic terminal base class that delegates output functions to derived classes
         *
         * Note: Terminals should only be used with fixed width fonts
         */

        class Terminal {

            protected:
                Size _terminalSize;
                Point _cursor;

            public:

                /**
                 * Constructor
                 */

                Terminal() {
                    _cursor.X=_cursor.Y=0;
                }

                /**
                 * Virtual destructor does nothing
                 */

                virtual ~Terminal() {}


                /**
                 * clear display
                 */

                virtual void clear()=0;


                /**
                 * Clear just the current line and reset x to 0
                 */

                virtual void clearLine()=0;

                /**
                 * Write whole string. Makes use of implementation of writeCharacter to do the work. Understands
                 * 0xd and 0xa as meaning 'new line'.
                 *
                 * @param[in] str The null terminated string to write.
                 */

                void writeString(const char *str) {
                    const char *ptr;

                    for(ptr=str;*ptr;ptr++) {
                        if(*ptr == '\n') {
                            incrementY();
                            _cursor.X=0;
                        } else if(*ptr=='\r') {
                            _cursor.X=0;
                        } else {
                            writeCharacter(_cursor.X,_cursor.Y,*ptr);

                            if(++_cursor.X >= _terminalSize.Width) {
                                _cursor.X=0;
                                incrementY();
                            }
                        }
                    }
                }

                /**
                 * Write character
                 *
                 * @param[in] x The column.
                 * @param[in] y The row.
                 * @param[in] c The character to write.
                 */

                virtual void writeCharacter(int16_t x,int16_t y,char c)=0;

                /**
                 * Increment Y pos
                 */

                virtual void incrementY()=0;

                /**
                 * Write a character.
                 *
                 * @param[in] c The character to write.
                 */

                void writeChar(char c) {
                    char buf[2];

                    buf[0]=c;
                    buf[1]='\0';

                    writeString(buf);
                }
        };

    }
}
