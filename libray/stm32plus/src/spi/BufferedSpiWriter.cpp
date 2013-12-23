/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "spi/BufferedSpiWriter.h"


namespace stm32plus {

    /**
     * Constructor
     * @param[in] underlyingWriter The SPI writer that we will flush to
     * @param[in] buffer The memory buffer that will collect pending data
     * @param[in] state The initial buffering state
     * @param[in] autoFlushThreshold If the buffer size reaches or exceeds this value then the
     *     buffer will be automatically flushed. Auto-flushing is not compatible with duplex mode reception of data. Set
     *  this to the default of zero to disabled auto-flushing.
     */

    BufferedSpiWriter::BufferedSpiWriter(SpiWriter& underlyingWriter,ByteArrayOutputStream& buffer,BufferingState state,uint32_t autoFlushThreshold)
        : SpiWriter(underlyingWriter.getPeripheral()),
            _buffer(buffer),
          _underlyingWriter(underlyingWriter) {

        _autoFlushThreshold=autoFlushThreshold;
        _bufferingState=state;
    }


    /*
     * Write to the buffer
     */

    bool BufferedSpiWriter::write(uint8_t *dataToSend,uint32_t numBytes,uint8_t *dataReceived) {

        bool retval;

        if(_bufferingState==BufferingEnabled) {

            if((retval=_buffer.write(dataToSend,numBytes)) && _autoFlushThreshold!=0 && _buffer.getSize()>=_autoFlushThreshold)
                retval=flush(NULL);

            return retval;
        }
        else
            return _underlyingWriter.write(dataToSend,numBytes,dataReceived);
    }


    /**
     * Flush the buffer to the peripheral. If the peripheral is operating in duplex
     * mode then receivedData may point to a buffer large enough to receive the same
     * number of bytes that are being sent.
     * @param receivedData The full-duplex received data buffer, or NULL if no received
     *   data is possible or required.
     * @return false if it fails
     */

    bool BufferedSpiWriter::flush(uint8_t *receivedData) {

        bool retval;

        // check for no data
        if(_buffer.getSize()==0)
            return true;

        // write to the peripheral

        _peripheral.setNss(false);

        retval=_underlyingWriter.write(_buffer.getBuffer(),_buffer.getSize(),receivedData);

        _peripheral.setNss(true);

        // clear the pending buffer
        _buffer.clear();
        return retval;
    }


    /**
     * Set the current state of buffering.
     * @param[in] newState The new buffering state
     */

    void BufferedSpiWriter::setBufferingState(BufferingState newState) {
        _bufferingState=newState;
    }

}
