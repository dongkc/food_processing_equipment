/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "display/graphic/PanelConfiguration.h"
#include "display/graphic/tft/mc2pa8201/commands/AllCommands.h"


namespace stm32plus {
    namespace display {


        /**
         * Template class holding the specialisation of MC2PA8201Colour for 16-bit colours
         * @tparam TAccessMode The access mode class (e.g. FSMC)
         */

        template<class TAccessMode>
        class MC2PA8201Colour<COLOURS_16BIT,TAccessMode> {

            private:
                TAccessMode& _accessMode;

            protected:
                MC2PA8201Colour(TAccessMode& accessMode);

                uint16_t getInterfacePixelFormat() const;

                typedef uint32_t tCOLOUR;

                struct UnpackedColour {
                  uint8_t first,second;
                };

          public:
                void unpackColour(tCOLOUR src,UnpackedColour& dest) const;
                void unpackColour(uint8_t red,uint8_t green,uint8_t blue,UnpackedColour& dest) const;

                void writePixel(const UnpackedColour& cr) const;
                void fillPixels(uint32_t numPixels,const UnpackedColour& cr) const;

                void allocatePixelBuffer(uint32_t numPixels,uint8_t*& buffer,uint32_t& bytesPerPixel) const;
                void rawTransfer(const void *data,uint32_t numPixels) const;
        };


        /**
         * Constructor
         */

        template<class TAccessMode>
        inline MC2PA8201Colour<COLOURS_16BIT,TAccessMode>::MC2PA8201Colour(TAccessMode& accessMode)
            : _accessMode(accessMode) {
        }


        /**
         * Get the register setting for 16-bit colours
         * @return 16-bit interface pixel format register setting
         */

        template<class TAccessMode>
        inline uint16_t MC2PA8201Colour<COLOURS_16BIT,TAccessMode>::getInterfacePixelFormat() const {
            return 0x55;
        }


        /**
         * Unpack the colour from rrggbb to the interal 5-6-5 format

     * 00000000RRRRRRRRGGGGGGGGBBBBBBBB ->
     * 0000000000000000RRRRRGGGGGGBBBBB

         * @param src rrggbb
         * @param dest The unpacked colour structure
         */

        template<class TAccessMode>
        inline void MC2PA8201Colour<COLOURS_16BIT,TAccessMode>::unpackColour(tCOLOUR src,UnpackedColour& dest) const {
            uint8_t r,g,b;

            r=src >> 16;
            g=src >> 8;
            b=src;

            r &= 0xf8;
            g &= 0xfc;
            b &= 0xf8;

            dest.first=b | (g>>5);
            dest.second=(g << 3) | (r >> 3);
        }

        /**
         * Unpack the colour from components to the internal format
         * @param red
         * @param green
         * @param blue
         * @param dest
         */

        template<class TAccessMode>
        inline void MC2PA8201Colour<COLOURS_16BIT,TAccessMode>::unpackColour(uint8_t red,uint8_t green,uint8_t blue,UnpackedColour& dest) const {

            red &= 0xf8;
            green &= 0xfc;
            blue &= 0xf8;

            dest.first=blue | (green>>5);
            dest.second=(green << 3) | (red >> 3);
        }


        /**
         * Write a single pixel to the current output position.
         * Assumes that the caller has already issued the beginWriting() command.
         * @param cr The pixel to write
         */

        template<class TAccessMode>
        inline void MC2PA8201Colour<COLOURS_16BIT,TAccessMode>::writePixel(const UnpackedColour& cr) const {
            this->_accessMode.writeData(cr.first);
            this->_accessMode.writeData(cr.second);
        }


        /**
         * Fill a block of pixels with the same colour. This operation will issue the
         * beginWriting() command for you.
         * @param numPixels how many
         * @param cr The unpacked colour to write
         */

        template<class TAccessMode>
        inline void MC2PA8201Colour<COLOURS_16BIT,TAccessMode>::fillPixels(uint32_t numPixels,const UnpackedColour& cr) const {

            uint8_t first,second;

            this->_accessMode.writeCommand(mc2pa8201::MEMORY_WRITE);

            first=cr.first;
            second=cr.second;

            while(numPixels--) {
                this->_accessMode.writeData(first);
                this->_accessMode.writeData(second);
            }
        }


        /**
         * Allocate a buffer for pixel data. You supply the number of pixels and this allocates the buffer as a uint8_t[].
         * Allocated buffers should be freed with delete[]
         *
         * @param numPixels The number of pixels to allocate
         * @param buffer The output buffer
         * @param bytesPerPixel Output the number of bytes per pixel
         */

        template<class TAccessMode>
        inline void MC2PA8201Colour<COLOURS_16BIT,TAccessMode>::allocatePixelBuffer(uint32_t numPixels,uint8_t*& buffer,uint32_t& bytesPerPixel) const {
          buffer=new uint8_t[numPixels*2];
          bytesPerPixel=2;
        }


        /**
         * Bulk-copy some pixels from the memory buffer to the LCD. The pixels must already be formatted ready
         * for transfer.
         * @param buffer The memory buffer
         * @param numPixels The number of pixels to transfer from the buffer
         */

        template<class TAccessMode>
        inline void MC2PA8201Colour<COLOURS_16BIT,TAccessMode>::rawTransfer(const void *buffer,uint32_t numPixels) const {

            volatile uint8_t *dataAddress=this->_accessMode.getDataAddress();
            const uint8_t *ptr=static_cast<const uint8_t *>(buffer);

            // two bytes per pixel

            while(numPixels--) {
                *dataAddress=*ptr++;
                *dataAddress=*ptr++;
            }
        }
    }
}
