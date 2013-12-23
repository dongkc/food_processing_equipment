/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include <cstdlib>
#include "display/character/HD44780.h"
#include "timing/MicrosecondDelay.h"


namespace stm32plus {
    namespace display {

        /**
         * Constructor: 8 bit I/O. Requires 8 GPIO pins for the data and 2 for the control signals. RW is fixed
         * for writing.
         */

        HD44780::HD44780(Gpio& rs,Gpio& enable,Gpio& d0,Gpio& d1,Gpio& d2,Gpio& d3,Gpio& d4,Gpio& d5,Gpio& d6,Gpio& d7) {
            initialise(false,&rs,NULL,&enable,&d0,&d1,&d2,&d3,&d4,&d5,&d6,&d7);
        }

        /**
         * Constructor: 8 bit I/O + RW. Requires 8 GPIO pins for the data and 3 for the control signals. RW is controlled
         * by this class.
         */

        HD44780::HD44780(Gpio& rs,Gpio& rw,Gpio& enable,Gpio& d0,Gpio& d1,Gpio& d2,Gpio& d3,Gpio& d4,Gpio& d5,Gpio& d6,Gpio& d7) {
            initialise(false,&rs,&rw,&enable,&d0,&d1,&d2,&d3,&d4,&d5,&d6,&d7);
        }

        /**
         * Constructor: 4 bit I/O + RW. Requires 4 GPIO pins for the data and 3 for the control signals. RW is controlled
         * by this class.
         */

        HD44780::HD44780(Gpio& rs,Gpio& rw,Gpio& enable,Gpio& d0,Gpio& d1,Gpio& d2,Gpio& d3) {
            initialise(true,&rs,&rw,&enable,&d0,&d1,&d2,&d3,NULL,NULL,NULL,NULL);
        }

        /**
         * Constructor: 4 bit I/O. This is the configuration that requires the fewest pins.
         */

        HD44780::HD44780(Gpio& rs,Gpio& enable,Gpio& d0,Gpio& d1,Gpio& d2,Gpio& d3) {
            initialise(true,&rs,NULL,&enable,&d0,&d1,&d2,&d3,NULL,NULL,NULL,NULL);
        }

        /*
         * Initialise
         */

        void HD44780::initialise(bool fourbitmode,Gpio* rs,Gpio* rw,Gpio* enable,Gpio* d0,Gpio* d1,Gpio* d2,Gpio* d3,Gpio* d4,Gpio* d5,Gpio* d6,Gpio* d7) {

            _rs_pin=rs;
            _rw_pin=rw;
            _enable_pin=enable;

            _data_pins[0]=d0;
            _data_pins[1]=d1;
            _data_pins[2]=d2;
            _data_pins[3]=d3;
            _data_pins[4]=d4;
            _data_pins[5]=d5;
            _data_pins[6]=d6;
            _data_pins[7]=d7;

            if(fourbitmode)
                _displayfunction=LCD_4BITMODE|LCD_1LINE|LCD_5x8DOTS;
            else
                _displayfunction=LCD_8BITMODE|LCD_1LINE|LCD_5x8DOTS;

            begin(16,1);
        }

        /**
         * Set up display size.
         * @param[in] cols The number of columns on this display
         * @param[in] lines The number of lines on this display
         * @param[in] dotsize The code for dot size of each character. Defaults to 0 (5x8 matrix)
         */

        void HD44780::begin(uint8_t cols,uint8_t lines,uint8_t dotsize) {

            if(lines>1)
                _displayfunction|=LCD_2LINE;

            _numlines=lines;
            _numcols=cols;
            _currline=0;

            // for some 1 line displays you can select a 10 pixel high font

            if(dotsize!=0&&lines==1)
                _displayfunction|=LCD_5x10DOTS;

            // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
            // according to datasheet, we need at least 40ms after power rises above 2.7V
            // before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50

            MicrosecondDelay::delay(50000);

            // Now we pull both RS and R/W low to begin commands
            _rs_pin->reset();
            _enable_pin->reset();

            if(_rw_pin)
                _rw_pin->reset();

            // put the LCD into 4 bit or 8 bit mode

            if(!(_displayfunction&LCD_8BITMODE)) {
                // this is according to the hitachi HD44780 datasheet figure 24, pg 46

                // we start in 8bit mode, try to set 4 bit mode
                write4bits(3);
                MicrosecondDelay::delay(4500);

                // second try
                write4bits(3);
                MicrosecondDelay::delay(4500);

                // third go!
                write4bits(3);
                MicrosecondDelay::delay(150);

                // finally, set to 8-bit interface
                write4bits(2);
            } else {
                // this is according to the hitachi HD44780 datasheet page 45 figure 23

                // Send function set command sequence
                sendCommand(LCD_FUNCTIONSET|_displayfunction);
                MicrosecondDelay::delay(4500); // wait more than 4.1ms

                // second try
                sendCommand(LCD_FUNCTIONSET|_displayfunction);
                MicrosecondDelay::delay(150);

                // third go
                sendCommand(LCD_FUNCTIONSET|_displayfunction);
            }

            // finally, set # lines, font size, etc.
            sendCommand(LCD_FUNCTIONSET|_displayfunction);

            // turn the display on with no cursor or blinking default
            _displaycontrol=LCD_DISPLAYON|LCD_CURSOROFF|LCD_BLINKOFF;
            setDisplay( DISPLAY_ON);

            // clear it off
            clear();

            // Initialize to default text direction
            _displaymode=LCD_ENTRYLEFT|LCD_ENTRYSHIFTDECREMENT;

            // set the entry mode
            sendCommand(LCD_ENTRYMODESET|_displaymode);
        }

        /*
         * clear display, set cursor position to zero
         */

        void HD44780::clear() {
            sendCommand( LCD_CLEARDISPLAY);
            MicrosecondDelay::delay(2000);
        }

        /*
         * Move the cursor to a position
         */

        void HD44780::moveCursor(uint8_t col,uint8_t row) {
            const int row_offsets[]= { 0x00,0x40,0x14,0x54 };

            if(row>_numlines)
                row=_numlines-1; // we count rows starting w/0

            sendCommand(LCD_SETDDRAMADDR|(col+row_offsets[row]));
        }

        /*
         * Turn the display on/off (quickly)
         */

        void HD44780::setDisplay(DisplayState newState_) {

            if(newState_==DISPLAY_ON)
                _displaycontrol|=LCD_DISPLAYON;
            else
                _displaycontrol&=~LCD_DISPLAYON;

            sendCommand(LCD_DISPLAYCONTROL|_displaycontrol);
        }

        /*
         * Turns the underline cursor on/off
         */

        void HD44780::setCursor(CursorState newState_) {

            if(newState_==CURSOR_ON)
                _displaycontrol|=LCD_CURSORON;
            else
                _displaycontrol&=~LCD_CURSORON;

            sendCommand(LCD_DISPLAYCONTROL|_displaycontrol);
        }

        /*
         * Turn on and off the blinking cursor
         */

        void HD44780::setBlink(BlinkState newState_) {

            if(newState_==BLINK_ON)
                _displaycontrol|=LCD_BLINKON;
            else
                _displaycontrol&=~LCD_BLINKON;

            sendCommand(LCD_DISPLAYCONTROL|_displaycontrol);
        }

        /*
         * These commands scroll the display without changing the RAM
         */

        void HD44780::scrollDisplay(ScrollDirection direction_) {
            if(direction_==SCROLL_LEFT)
                sendCommand(LCD_CURSORSHIFT|LCD_DISPLAYMOVE|LCD_MOVELEFT);
            else
                sendCommand(LCD_CURSORSHIFT|LCD_DISPLAYMOVE|LCD_MOVERIGHT);
        }

        /*
         * Text direction
         */

        void HD44780::setTextDirection(TextDirection direction_) {

            if(direction_==TEXT_DIRECTION_LR)
                _displaymode|=LCD_ENTRYLEFT;
            else
                _displaymode&=~LCD_ENTRYLEFT;

            sendCommand(LCD_ENTRYMODESET|_displaymode);
        }

        /*
         * Set auto-scroll
         */

        void HD44780::setAutoScroll(AutoScrollState newState_) {

            if(newState_==AUTO_SCROLL_ON)
                _displaymode|=LCD_ENTRYSHIFTINCREMENT;
            else
                _displaymode&=~LCD_ENTRYSHIFTINCREMENT;

            sendCommand(LCD_ENTRYMODESET|_displaymode);
        }

        /**
         * Allows us to fill the first 8 CGRAM locations with custom characters
         * @param[in] location The custom character code (0..7)
         * @param[in] charmap The 8 bytes that define this character.
         */

        void HD44780::createCustomChar(uint8_t location,uint8_t charmap[]) {

            location&=7; // we only have 8 locations 0-7
            sendCommand(LCD_SETCGRAMADDR|(location<<3));

            for(int i=0;i<8;i++)
                write(charmap[i]);
        }

        /**
         * send a command byte
         * @param[in] value The command byte to send.
         */

        void HD44780::sendCommand(uint8_t value) {
            send(value,false);
        }

        /*
         * Write a character
         */

        void HD44780::write(uint8_t value) {
            send(value,true);
        }

        /*
         * write either command or data, with automatic 4/8-bit selection
         */

        void HD44780::send(uint8_t value,uint8_t mode) {

            // set mode
            _rs_pin->setState(mode);

            // if there is a RW pin indicated, set it low to Write
            if(_rw_pin)
                _rw_pin->reset();

            if(_displayfunction & LCD_8BITMODE) {
                write8bits(value);
            } else {
                write4bits(value>>4);
                write4bits(value);
            }
        }

        /*
         * Enable pulse
         */

        void HD44780::pulseEnable(void) {

            _enable_pin->reset();
            MicrosecondDelay::delay(1);

            _enable_pin->set();
            MicrosecondDelay::delay(1); // (anything>450ns)

            _enable_pin->reset();
            MicrosecondDelay::delay(80); // commands need > 37us to settle
        }

        /*
         * write 4 bits
         */

        void HD44780::write4bits(uint8_t value) {

            for(int i=0;i<4;i++)
                _data_pins[i]->setState((value>>i)&1);

            pulseEnable();
        }

        /*
         * Write 8 bits
         */

        void HD44780::write8bits(uint8_t value) {

            for(int i=0;i<8;i++)
                _data_pins[i]->setState((value>>i)&1);

            pulseEnable();
        }


        /*
         * Get the width
         */

        uint16_t HD44780::getWidth() {
            return _numcols;
        }


        /*
         * Get the height
         */

        uint16_t HD44780::getHeight() {
            return _numlines;
        }

    }
}
