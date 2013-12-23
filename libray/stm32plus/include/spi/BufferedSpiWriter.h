/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "stream/ByteArrayOutputStream.h"
#include "spi/SpiWriter.h"


namespace stm32plus {


    /**
     * @brief Buffered SPI writer holds data in a memory buffer before writing in bulk.
     */

    class BufferedSpiWriter : public SpiWriter {

        public:

        /**
             * Functional state of buffering - buffering can be disabled/enabled at will
             */

            enum BufferingState {

                /// buffering is enabled
                BufferingEnabled,

                /// buffering is disabled, writes will go through to the peripheral
                BufferingDisabled
            };


        protected:
            ByteArrayOutputStream& _buffer;
            SpiWriter& _underlyingWriter;
            BufferingState _bufferingState;
            uint32_t _autoFlushThreshold;

        public:
            BufferedSpiWriter(
                    SpiWriter& underlyingWriter,
                    ByteArrayOutputStream& buffer,
                    BufferingState state=BufferingEnabled,
                    uint32_t autoFlushThreshold=0);

            bool flush(uint8_t *receivedData=NULL);
            void setBufferingState(BufferingState newState);

            // overrides from SPI writer
            virtual bool write(uint8_t *dataToSend,uint32_t numBytes,uint8_t *dataReceived=NULL);
    };
}
