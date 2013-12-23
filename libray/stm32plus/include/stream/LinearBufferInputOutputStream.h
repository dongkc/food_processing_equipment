/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once


#include "stream/BufferedInputOutputStream.h"


namespace stm32plus {

    /**
     * @brief Class to support a linear I/O buffer.
     *
     * The buffer has a start and an end and
     * does not wrap around like the circular buffer. The reset() call can be used to reset
     * both the input pointer and the resetOutput() call can be used to reset the output pointer.
     */

    class LinearBufferInputOutputStream : public BufferedInputOutputStream {
        public:

            // constructors

            LinearBufferInputOutputStream(uint8_t *buffer,uint32_t size);
            LinearBufferInputOutputStream(uint32_t initialSize);

            void resetOutput();

            // overrides from InputStream

            virtual int16_t read();
            virtual bool read(void *buffer,uint32_t size,uint32_t& actuallyRead);
            virtual bool skip(uint32_t howMuch);
            virtual bool available();
            virtual bool reset();

            // overrides from OutputStream

            virtual bool write(uint8_t c);
            virtual bool write(const void *buffer,uint32_t size);

            virtual bool flush() {
                return true;
            }

            // overrides from both

            virtual bool close() {
                return true;
            }
    };
}
