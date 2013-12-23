/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "stream/LzgDecompressionInputStream.h"
#include "error/ErrorProvider.h"


static const uint8_t LZG_LENGTH_DECODE_LUT[32]= { 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,35,48,72,128 };


namespace stm32plus {


    /**
     * Constructor. Initiates the decompression.
     * The error provider should be checked to ensure that nothing went wrong
     * while setting up the decompressor
     *
     * @param input The source of compressed bytes
     * @param compressedSize the number of bytes of compressed data
     */

    LzgDecompressionStream::LzgDecompressionStream(InputStream& input,uint32_t compressedSize)
        : _input(input),
          _compressedSize(compressedSize) {

        int i;

        // no error yet

        errorProvider.clear();

        // initialize the output byte buffer

        _compressedDataAvailable=_compressedSize;
        _historyCopyDataAvailable=0;

        _dst=_circbuf;
        _dstEnd=_circbuf+sizeof(_circbuf);

        // skip header information

        if(!input.skip(16))
            return;

        // Get marker symbols from the input stream

        _input >> _marker1;
        _input >> _marker2;
        _input >> _marker3;
        _input >> _marker4;

        _compressedDataAvailable-=20;                      // the header and 4 markers

        // Initialize marker symbol LUT

        for(i=0;i<256;++i)
            _isMarkerSymbolLUT[i]=0;

        _isMarkerSymbolLUT[_marker1]=1;
        _isMarkerSymbolLUT[_marker2]=1;
        _isMarkerSymbolLUT[_marker3]=1;
        _isMarkerSymbolLUT[_marker4]=1;
    }


    /*
     * Read a byte from the stream, or return EOF or an error
     */

    int16_t LzgDecompressionStream::read() {

        uint8_t nextByte;

        // check for end of stream

        if(_historyCopyDataAvailable==0 && _compressedDataAvailable==0)
            return E_END_OF_STREAM;

        // return the next byte

        if(readNextUncompressedByte(nextByte))
            return nextByte;

        return false;
    }


    bool LzgDecompressionStream::read(void *buffer,uint32_t size,uint32_t& actuallyRead) {

        uint8_t *ptr;

        ptr=static_cast<uint8_t *>(buffer);
        actuallyRead=0;

        while(size-- && available()) {

            if(!readNextUncompressedByte(*ptr++))
                return false;

            actuallyRead++;
        }

        return true;
    }


    /*
     * Can't close, and can't go wrong either
     */

    bool LzgDecompressionStream::close() {
        return true;
    }


    /*
     * Can't skip
     */

    bool LzgDecompressionStream::skip(uint32_t howMuch __attribute__((unused))) {
        return errorProvider.set(ErrorProvider::ERROR_PROVIDER_LZG_DECOMPRESSION_STREAM,E_OPERATION_NOT_SUPPORTED);
    }


    /*
     * Return true if there is data available
     */

    bool LzgDecompressionStream::available() {
        return _compressedDataAvailable>0 || _historyCopyDataAvailable>0;
    }


    /*
     * Cannot reset because we can't guarantee that the compressed data
     * started at the beginning of the input stream
     */

    bool LzgDecompressionStream::reset() {
        return errorProvider.set(ErrorProvider::ERROR_PROVIDER_LZG_DECOMPRESSION_STREAM,E_OPERATION_NOT_SUPPORTED);
    }


    /*
     * Read the next uncompressed byte from the stream
     */

    bool LzgDecompressionStream::readNextUncompressedByte(uint8_t& nextByte) {

        uint8_t symbol,b,b2;
        uint16_t offset,length;

        // if we're in mid-copy from the history window, take the next byte from there

        if(_historyCopyDataAvailable>0) {
            nextByte=getByteFromHistoryCopy();
            return true;
        }

        // get the next symbol

        if(!nextByteFromStream(symbol))
            return false;

        // Marker symbol?

        if(!_isMarkerSymbolLUT[symbol]) {

            // Literal copy

            nextByte=symbol;

            *_dst++=symbol;
            if(_dst==_dstEnd)
                _dst=_circbuf;
        } else {

            if(!nextByteFromStream(b))
                return false;

            if(b) {

                // Decode offset / length parameters

                if(symbol == _marker1) {

                    // distant copy is not supported on the STM32 due to lack of SRAM)

                    return errorProvider.set(ErrorProvider::ERROR_PROVIDER_LZG_DECOMPRESSION_STREAM,E_UNSUPPORTED_COMPRESSED_DATA);

                } else if(symbol == _marker2) {

                    // Medium copy

                    length=LZG_LENGTH_DECODE_LUT[b & 0x1f];

                    if(!nextByteFromStream(b2))
                        return false;

                    offset=(((uint16_t)(b & 0xe0)) << 3) | b2;
                    offset+=8;
                } else if(symbol == _marker3) {

                    // Short copy

                    length=(b >> 6) + 3;
                    offset=(b & 0x3f) + 8;
                } else {

                    // Near copy (including RLE)

                    length=LZG_LENGTH_DECODE_LUT[b & 0x1f];
                    offset=(b >> 5) + 1;
                }

                // Copy corresponding data from history window

                if(offset<=static_cast<uint16_t>(_dst-_circbuf))
                    _historyCopyPosition=_dst-offset;
                else
                    _historyCopyPosition=_dstEnd-(offset-(uint16_t)(_dst-_circbuf));

                _historyCopyDataAvailable=length;

                nextByte=getByteFromHistoryCopy();

            } else {

                // single occurance of a marker symbol

                nextByte=symbol;

                *_dst++=symbol;
                if(_dst==_dstEnd)
                    _dst=_circbuf;
            }
        }

        return true;
    }


    /*
     * Get next byte from input stream
     */

    bool LzgDecompressionStream::nextByteFromStream(uint8_t& nextByte) {

        int16_t value;

        // must have a byte to read

        if(_compressedSize==0)
            return errorProvider.set(ErrorProvider::ERROR_PROVIDER_LZG_DECOMPRESSION_STREAM,E_END_OF_STREAM);

        // read next byte

        if((value=_input.read())<0)
            return false;

        // return it

        nextByte=value;
        _compressedSize--;

        return true;
    }


    /*
     * Get one byte from the available data in this history window.
     * Data must be available!
     */

    uint8_t LzgDecompressionStream::getByteFromHistoryCopy() {

        uint8_t retval;

        // get the next value from the copy position, copy back to the circular buffer

        retval=*_historyCopyPosition++;
        *_dst++=retval;

        // copy position and source pointer are both in the circular buffer and must be updated

        if(_dst==_dstEnd)
            _dst=_circbuf;

        if(_historyCopyPosition==_dstEnd)
            _historyCopyPosition=_circbuf;

        // that's one less byte available for next time

        _historyCopyDataAvailable--;

        return retval;
    }


#if 0
    /*
     * LZG decoder. Calling this costs you 2K of stack space.
     */

    void Nokia6300LcdXmemImpl::lzgDecode(uint32_t in,uint32_t insize) {

        uint8_t *dst,*dstEnd,*copy,symbol,b,b2;
        uint8_t marker1,marker2,marker3,marker4;
        uint32_t inEnd,src;
        uint16_t offset,length,i;
        char isMarkerSymbolLUT[256];
        uint8_t circbuf[2056];          // this is the history buffer

        // Initialize the byte streams
        src=in;
        inEnd=in+insize;
        dst=circbuf;
        dstEnd=circbuf+sizeof(circbuf);

        // Skip header information
        src+=16;

        // Get marker symbols from the input stream
        marker1=lzgReadNextByte(src++);
        marker2=lzgReadNextByte(src++);
        marker3=lzgReadNextByte(src++);
        marker4=lzgReadNextByte(src++);

        // Initialize marker symbol LUT
        for(i=0;i<256;++i)
            isMarkerSymbolLUT[i]=0;

        isMarkerSymbolLUT[marker1]=1;
        isMarkerSymbolLUT[marker2]=1;
        isMarkerSymbolLUT[marker3]=1;
        isMarkerSymbolLUT[marker4]=1;

        // Main decompression loop
        while(src<inEnd) {
            // Get the next symbol
            symbol=lzgReadNextByte(src++);

            // Marker symbol?
            if(!isMarkerSymbolLUT[symbol]) {

                // Literal copy

                XMEM_WRITE_DATA_ADDRESS(symbol);
                *dst++=symbol;
                if(dst==dstEnd)
                    dst=circbuf;

            } else {

                b=lzgReadNextByte(src++);

                if(b) {

                    // Decode offset / length parameters

                    if(symbol == marker1) {
                        // Distant copy is not supported on the Arduino due to lack of memory
                        return;
                    } else if(symbol == marker2) {

                        // Medium copy

                        length=LZG_LENGTH_DECODE_LUT[b & 0x1f];
                        b2=lzgReadNextByte(src++);
                        offset=(((uint16_t)(b & 0xe0)) << 3) | b2;
                        offset+=8;
                    } else if(symbol == marker3) {

                        // Short copy

                        length=(b >> 6) + 3;
                        offset=(b & 0x3f) + 8;
                    } else {

                        // Near copy (including RLE)

                        length=LZG_LENGTH_DECODE_LUT[b & 0x1f];
                        offset=(b >> 5) + 1;
                    }

                    // Copy corresponding data from history window

                    if(offset<=static_cast<uint16_t>(dst-circbuf))
                        copy=dst-offset;
                    else
                        copy=dstEnd-(offset-(uint16_t)(dst-circbuf));

                    for(i=0;i<length;i++) {
                        XMEM_WRITE_DATA_ADDRESS(*copy);

                        *dst++=*copy++;

                        if(dst==dstEnd)
                            dst=circbuf;

                        if(copy==dstEnd)
                            copy=circbuf;
                    }

                } else {
                    // Single occurance of a marker symbol...
                    XMEM_WRITE_DATA_ADDRESS(symbol);
                    *dst++=symbol;
                    if(dst==dstEnd)
                        dst=circbuf;
                }
            }
        }
    }
#endif
}
