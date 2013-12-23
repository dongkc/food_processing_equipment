/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "display/graphic/GraphicsLibrary.h"
#include "string/StringUtil.h"
#include "stream/OutputStream.h"


namespace stm32plus {
    namespace display {

        /**
         * Base class to manage the display as a character terminal. Derivations for both landscape
         * and portrait mode are supplied. Hardware scrolling is supported in portrait mode. In landscape
         * mode the terminal will clear and restart at the top when the end is reached.
         *
         * The font must be fixed width or wierd stuff will happen.
         *
         * This class implements output stream so it can be used as a sink for data sourced from other
         * places. For example, see ConnectedInputOutputStream for a plumbing class that can be used to join an
         * input stream to an output stream.
         */

        template<class TImpl,class TGraphicsLibrary>
        class GraphicTerminalBase : public OutputStream {

            protected:

                TGraphicsLibrary *_gl;
                const Font *_font;
                bool _autoLineFeed;

                Size _terminalSize;
                Size _fontSize;
                Point _cursor;

            protected:
                void calcTerminalSize();
                void incrementY();

            public:
                GraphicTerminalBase(
                        TGraphicsLibrary *gl,
                        const Font *font,
                        bool autoLineFeed);

                virtual ~GraphicTerminalBase() {}

                void writeCharacter(char c);
                void writeString(const char *str);

                GraphicTerminalBase& operator<<(const char *str);
                GraphicTerminalBase& operator<<(char c);
                GraphicTerminalBase& operator<<(int32_t val);
                GraphicTerminalBase& operator<<(uint32_t val);
                GraphicTerminalBase& operator<<(int16_t val);
                GraphicTerminalBase& operator<<(uint16_t val);
                GraphicTerminalBase& operator<<(const DoublePrecision& val);
                GraphicTerminalBase& operator<<(double val);

                void clearScreen();
                void clearLine();

                // overrides from OutputStream

                virtual bool write(uint8_t c);
                virtual bool write(const void *buffer,uint32_t size);

                virtual bool close() { return true; }
                virtual bool flush() { return true; }
        };


        /**
         * Constructor. You probably want to call clearScreen before you get going.
         * The font will default to the one selected for stream IO if none is supplied.
         *
         * @param gl The graphics library (LCD implementation class) to use
         * @param font The font to use, or NULL to get it from the graphics library selection
         * @param autoLineFeed true to add a line feed when a carriage return is received.
         */

        template<class TImpl,class TGraphicsLibrary>
        GraphicTerminalBase<TImpl,TGraphicsLibrary>::GraphicTerminalBase(
                TGraphicsLibrary *gl,
                const Font *font,
                bool autoLineFeed)
            : _gl(gl),
                _font(font==NULL ? gl->getStreamSelectedFont() : font),
                _autoLineFeed(autoLineFeed) {

            calcTerminalSize();
        }


        /**
         * Calculate the terminal size, in characters.
         */

        template<class TImpl,class TGraphicsLibrary>
        void GraphicTerminalBase<TImpl,TGraphicsLibrary>::calcTerminalSize() {

            const FontChar *fc;

            // need to know the width of the characters. They're all the same so measure a space.

            _font->getCharacter(static_cast<uint8_t>(' '),fc);

            _fontSize.Height=_font->getHeight();
            _fontSize.Width=fc->PixelWidth;

            // height is rounded down if the fixed lines don't sum to a multiple of the font height

            _terminalSize.Width=_gl->getWidth()/fc->PixelWidth;
            _terminalSize.Height=_gl->getHeight()/_font->getHeight();
        }


        /**
         * Clear the screen
         */

        template<class TImpl,class TGraphicsLibrary>
        void GraphicTerminalBase<TImpl,TGraphicsLibrary>::clearScreen() {

            // clear the display

            _gl->clearScreen();

            this->_cursor.X=0;
            this->_cursor.Y=0;

            // allow the derivation to reset any parameters

            static_cast<TImpl *>(this)->reset();
        }


        /**
         * Clear just the current line
         */

        template<class TImpl,class TGraphicsLibrary>
        void GraphicTerminalBase<TImpl,TGraphicsLibrary>::clearLine() {

            Rectangle rc;

            rc.X=0;
            rc.Y=(_cursor.Y % _terminalSize.Height)*_fontSize.Height;
            rc.Height=_fontSize.Height;
            rc.Width=_terminalSize.Width*_fontSize.Width;

            _gl->clearRectangle(rc);

            _cursor.X=0;
        }


        /**
         * Write a line to the display
         */

        template<class TImpl,class TGraphicsLibrary>
        void GraphicTerminalBase<TImpl,TGraphicsLibrary>::writeString(const char *str) {

            const char *ptr;

            for(ptr=str;*ptr;writeCharacter(*ptr++));
        }


        /**
         * Write a character to the display
         */

        template<class TImpl,class TGraphicsLibrary>
        void GraphicTerminalBase<TImpl,TGraphicsLibrary>::writeCharacter(char c) {

            char buffer[2];
            Point p;

            if(c=='\n') {

                incrementY();
                _cursor.X=0;

            } else if(c=='\r') {

                if(_autoLineFeed)
                    incrementY();

                _cursor.X=0;
            } else {

                // scale up the x,y character co-ords to pixel co-ords

                p.X=_cursor.X*_fontSize.Width;
                p.Y=(_cursor.Y % _terminalSize.Height)*_fontSize.Height;

                // create a string

                buffer[0]=c;
                buffer[1]='\0';

                // move the cursor and write

                _gl->writeString(p,*_font,buffer);

                if(++_cursor.X >= _terminalSize.Width) {
                    _cursor.X=0;
                    incrementY();
                }
            }
        }


        /**
         * Increment the row and scroll if we have hit the bottom. If the LCD implementation supports
         * hardware scrolling then we will use it, otherwise we just clear the display and start again
         * at the top left.
         */

        template<class TImpl,class TGraphicsLibrary>
        void GraphicTerminalBase<TImpl,TGraphicsLibrary>::incrementY() {

            _cursor.Y++;

            if(_cursor.Y>=_terminalSize.Height)
                static_cast<TImpl *>(this)->scroll();
        }


        /**
         * Write a string using the stream operator
         */

        template<class TImpl,class TGraphicsLibrary>
        GraphicTerminalBase<TImpl,TGraphicsLibrary>& GraphicTerminalBase<TImpl,TGraphicsLibrary>::operator<<(const char *str) {

            writeString(str);
            return *this;
        }

        /**
         * Write a character
         */

        template<class TImpl,class TGraphicsLibrary>
        GraphicTerminalBase<TImpl,TGraphicsLibrary>& GraphicTerminalBase<TImpl,TGraphicsLibrary>::operator<<(char c) {

            writeCharacter(c);
            return *this;
        }

        /**
         * Write a 16 bit signed int
         */

        template<class TImpl,class TGraphicsLibrary>
        GraphicTerminalBase<TImpl,TGraphicsLibrary>& GraphicTerminalBase<TImpl,TGraphicsLibrary>::operator<<(int16_t val) {

          return operator<<((int32_t)val);
        }

        /**
         * Write a 16 bit unsigned int
         */

        template<class TImpl,class TGraphicsLibrary>
        GraphicTerminalBase<TImpl,TGraphicsLibrary>& GraphicTerminalBase<TImpl,TGraphicsLibrary>::operator<<(uint16_t val) {

          return operator<<((int32_t)val);
        }

        /**
         * Write a 32 bit signed int
         */

        template<class TImpl,class TGraphicsLibrary>
        GraphicTerminalBase<TImpl,TGraphicsLibrary>& GraphicTerminalBase<TImpl,TGraphicsLibrary>::operator<<(int32_t val) {

            char buf[15];
            StringUtil::itoa(val,buf,10);
            writeString(buf);

            return *this;
        }

        /**
         * Write a 32 bit unsigned int
         */

        template<class TImpl,class TGraphicsLibrary>
        GraphicTerminalBase<TImpl,TGraphicsLibrary>& GraphicTerminalBase<TImpl,TGraphicsLibrary>::operator<<(uint32_t val) {

            char buf[15];
            StringUtil::modp_uitoa10(val,buf);
            writeString(buf);

            return *this;
        }

        /**
         * Write a double precision value with 5 fractional digits
         */

        template<class TImpl,class TGraphicsLibrary>
        GraphicTerminalBase<TImpl,TGraphicsLibrary>& GraphicTerminalBase<TImpl,TGraphicsLibrary>::operator<<(double val) {

            return operator<<(DoublePrecision(val,TGraphicsLibrary::MAX_DOUBLE_FRACTION_DIGITS));
        }

        /**
         * Write a double precision value with customisable fractional digits
         */

        template<class TImpl,class TGraphicsLibrary>
        GraphicTerminalBase<TImpl,TGraphicsLibrary>& GraphicTerminalBase<TImpl,TGraphicsLibrary>::operator<<(const DoublePrecision& val) {

            char buf[25];

            StringUtil::modp_dtoa(val.Value,val.Precision,buf);
            writeString(buf);
            return *this;
        }


        /**
         * Write a single byte
         * @param c The byte to write
         * @return always true
         */

        template<class TImpl,class TGraphicsLibrary>
        bool GraphicTerminalBase<TImpl,TGraphicsLibrary>::write(uint8_t c) {
            return write(&c,1);
        }


        /**
         * Write many bytes. Each byte must be interpretable as a character to from the selected
         * font for this to make any sense. Random binary input will result in odd things.
         * @param[in] buffer The buffer of bytes
         * @param[in] size The number of bytes to write
         * @return always true
         */

        template<class TImpl,class TGraphicsLibrary>
        bool GraphicTerminalBase<TImpl,TGraphicsLibrary>::write(const void *buffer,uint32_t size) {

            const char *ptr=reinterpret_cast<const char *>(buffer);

            while(size--)
                this->writeCharacter(*ptr++);

            return true;
        }
    }
}
