/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "stream/OutputStream.h"
#include "memory/Memblock.h"


namespace stm32plus {

    /**
     * @brief output stream for writing to an auto-resizing memory block
     *
     * This stream writes to a memory block allocated on the heap that automaticall
     * increases to take new data. The intial size and the size of subsequent
     * resizes are customizable.
     */

    class ByteArrayOutputStream : public OutputStream {

        protected:
            ByteMemblock _memblock;
            uint32_t _currentUsage;
            uint32_t _resizeAmount;
            uint32_t _initialSize;

        public:
            ByteArrayOutputStream(uint32_t initialSize=100,uint32_t resizeAmount=100);
            virtual ~ByteArrayOutputStream() {}

            uint32_t getSize() const;
            uint8_t *getBuffer() const;

            void clear();

            // overrides from OutputStream

            virtual bool write(uint8_t c);
            virtual bool write(const void *buffer,uint32_t size);
            virtual bool close();
            virtual bool flush();
    };
}
