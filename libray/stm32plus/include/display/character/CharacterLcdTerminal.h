/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#pragma once

#include "display/Terminal.h"
#include "display/character/CharacterLcd.h"

namespace stm32plus {
    namespace display {

        /**
         * Character LCD terminal class.
         *
         * Example usage:
         *
         * @code
         * GpioPort pb(GPIOB);
         * pb.initialise(GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
         * HD44780 lcd(pb[11],pb[10],pb[12],pb[13],pb[14],pb[15]);
       * lcd.begin(20,4);
         * lcd.clear();
       * CharacterLcdTerminal terminal(lcd);
       * @endcode
         */

        class CharacterLcdTerminal : public Terminal {

            protected:
                CharacterLcd& _lcd;
                char *_framebuffer;

            public:
                CharacterLcdTerminal(CharacterLcd& lcd);
                virtual ~CharacterLcdTerminal();

                // overrides from Terminal

                virtual void writeCharacter(int16_t x,int16_t y,char c);
                virtual void incrementY();
                virtual void clear();
                virtual void clearLine();
        };
    }
}

