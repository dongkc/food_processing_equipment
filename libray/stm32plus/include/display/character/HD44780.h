/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#pragma once

#include "CharacterLcd.h"
#include "gpio/Gpio.h"

namespace stm32plus {
    namespace display {

        /**
         * HD44780 compatible displays. This class is derived from the LiquidCrystal class
         * included with the Arduino (AVR) libraries.
         *
         * Typical usage of this class for a 20x4 LCD:
         *
         * @code
         * GpioPort pb(GPIOB);
         * pb.initialise(GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
         * HD44780 lcd(pb[11],pb[10],pb[12],pb[13],pb[14],pb[15]);
       * lcd.begin(20,4);
       * @endcode
         */

        class HD44780 : public CharacterLcd {

            protected:
                Gpio* _rs_pin; // LOW: command.  HIGH: character.
                Gpio* _rw_pin; // LOW: write to LCD.  HIGH: read from LCD.
                Gpio* _enable_pin; // activated by a HIGH pulse.
                Gpio* _data_pins[8];

                uint8_t _displayfunction;
                uint8_t _displaycontrol;
                uint8_t _displaymode;

                uint8_t _initialized;

                uint8_t _numlines,_currline,_numcols;

                static const uint8_t LCD_CLEARDISPLAY=0x01;
                static const uint8_t LCD_RETURNHOME=0x02;
                static const uint8_t LCD_ENTRYMODESET=0x04;
                static const uint8_t LCD_DISPLAYCONTROL=0x08;
                static const uint8_t LCD_CURSORSHIFT=0x10;
                static const uint8_t LCD_FUNCTIONSET=0x20;
                static const uint8_t LCD_SETCGRAMADDR=0x40;
                static const uint8_t LCD_SETDDRAMADDR=0x80;

                // flags for display entry mode
                static const uint8_t LCD_ENTRYRIGHT=0x00;
                static const uint8_t LCD_ENTRYLEFT=0x02;
                static const uint8_t LCD_ENTRYSHIFTINCREMENT=0x01;
                static const uint8_t LCD_ENTRYSHIFTDECREMENT=0x00;

                // flags for display on/off control
                static const uint8_t LCD_DISPLAYON=0x04;
                static const uint8_t LCD_DISPLAYOFF=0x00;
                static const uint8_t LCD_CURSORON=0x02;
                static const uint8_t LCD_CURSOROFF=0x00;
                static const uint8_t LCD_BLINKON=0x01;
                static const uint8_t LCD_BLINKOFF=0x00;

                // flags for display/cursor shift
                static const uint8_t LCD_DISPLAYMOVE=0x08;
                static const uint8_t LCD_CURSORMOVE=0x00;
                static const uint8_t LCD_MOVERIGHT=0x04;
                static const uint8_t LCD_MOVELEFT=0x00;

                // flags for function set
                static const uint8_t LCD_8BITMODE=0x10;
                static const uint8_t LCD_4BITMODE=0x00;
                static const uint8_t LCD_2LINE=0x08;
                static const uint8_t LCD_1LINE=0x00;
                static const uint8_t LCD_5x10DOTS=0x04;
                static const uint8_t LCD_5x8DOTS=0x00;

            protected:
                void send(uint8_t,uint8_t);
                void write4bits(uint8_t);
                void write8bits(uint8_t);
                void pulseEnable();

                void initialise(bool fourbitmode,Gpio* rs,Gpio* rw,Gpio* enable,Gpio* d0,Gpio* d1,Gpio* d2,Gpio* d3,Gpio* d4,Gpio* d5,Gpio* d6,Gpio* d7);

            public:
                HD44780(Gpio& rs,Gpio& enable,Gpio& d0,Gpio& d1,Gpio& d2,Gpio& d3,Gpio& d4,Gpio& d5,Gpio& d6,Gpio& d7);
                HD44780(Gpio& rs,Gpio& rw,Gpio& enable,Gpio& d0,Gpio& d1,Gpio& d2,Gpio& d3,Gpio& d4,Gpio& d5,Gpio& d6,Gpio& d7);
                HD44780(Gpio& rs,Gpio& rw,Gpio& enable,Gpio& d0,Gpio& d1,Gpio& d2,Gpio& d3);
                HD44780(Gpio& rs,Gpio& enable,Gpio& d0,Gpio& d1,Gpio& d2,Gpio& d3);

                void begin(uint8_t cols,uint8_t rows,uint8_t charsize=LCD_5x8DOTS);

                virtual void createCustomChar(uint8_t,uint8_t[]);
                virtual void sendCommand(uint8_t);

                // overrides from CharacterLcd

                virtual void clear();
                virtual void moveCursor(uint8_t x_,uint8_t y_);
                virtual void write(uint8_t char_);

                virtual void setDisplay(DisplayState newState_);
                virtual void setBlink(BlinkState newState_);
                virtual void setCursor(CursorState newState_);
                virtual void scrollDisplay(ScrollDirection direction_);
                virtual void setTextDirection(TextDirection direction_);
                virtual void setAutoScroll(AutoScrollState newState_);

                virtual uint16_t getWidth();
                virtual uint16_t getHeight();
        };
    }
}

