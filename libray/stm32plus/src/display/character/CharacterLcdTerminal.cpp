/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include <cstring>
#include "display/character/CharacterLcdTerminal.h"

namespace stm32plus {
    namespace display {

        /**
         * Constructor. Allocates width*height bytes for a framebuffer.
         *
         * @param lcd The character LCD implementation to use as the output driver
         * for this terminal. The caller owns this class and should not destroy it
         * during the life of this class.
         */

        CharacterLcdTerminal::CharacterLcdTerminal(CharacterLcd& lcd) :
            _lcd(lcd) {

            _terminalSize.Width=lcd.getWidth();
            _terminalSize.Height=lcd.getHeight();

            _framebuffer=new char[_terminalSize.Width*_terminalSize.Height];
            memset(_framebuffer,' ',_terminalSize.Width*_terminalSize.Height);
        }


        /**
         * Destructor. Free memory used by the framebuffer.
         */

        CharacterLcdTerminal::~CharacterLcdTerminal() {
            delete [] _framebuffer;
        }


        /**
         * Clear the terminal
         */

        void CharacterLcdTerminal::clear() {

            _cursor.X=0;
            _cursor.Y=0;
            memset(_framebuffer,' ',_terminalSize.Width*_terminalSize.Height);
            _lcd.clear();
        }


        /**
         * Clear just the current line
         */

        void CharacterLcdTerminal::clearLine() {

            int16_t i;

            // move to start of line and clear the framebuffer line

            _cursor.X=0;
            memset(&_framebuffer[_cursor.Y*_terminalSize.Width],' ',_terminalSize.Width);
            _lcd.moveCursor(0,_cursor.Y);

            // write out spaces to clear the line

            for(i=0;i<_terminalSize.Width;i++)
                _lcd.write(' ');
        }


        /**
         * Write a character to the terminal at the co-ordinates.
         *
         * @param x The row.
         * @param y The column.
         * @param c the character to write.
         */

        void CharacterLcdTerminal::writeCharacter(int16_t x,int16_t y,char c) {

        // write the character to the display

            _lcd.moveCursor(x,y);
            _lcd.write(c);

        // and the framebuffer

            _framebuffer[x+y*_terminalSize.Width]=c;
        }


        /**
         * Increment the Y co-ordinate. Incrementing past the physical size of the display
         * scrolls the display vertically and keeps the y-co-ordinate at the bottom. The act
         * of scrolling will refresh the entire display.
         */

        void CharacterLcdTerminal::incrementY() {

            int16_t x,y;
            char *ptr;

        // easy if not yet at the bottom of the display

            if(_cursor.Y!=_terminalSize.Height-1)
                _cursor.Y++;
            else {
            // now we 'scroll' the framebuffer and clear out the last line

                memmove(_framebuffer,_framebuffer+_terminalSize.Width,_terminalSize.Width*(_terminalSize.Height-1));
                memset(_framebuffer+_terminalSize.Width*(_terminalSize.Height-1),' ',_terminalSize.Width);

            // refresh the whole frame

                ptr=_framebuffer;
                for(y=0;y<_terminalSize.Height;y++) {
                    for(x=0;x<_terminalSize.Width;x++) {

                        _lcd.moveCursor(x,y);
                        _lcd.write(*ptr++);
                    }
                }
            }
        }
    }
}
