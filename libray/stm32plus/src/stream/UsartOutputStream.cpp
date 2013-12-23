/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "stream/UsartOutputStream.h"

namespace stm32plus {

    /**
     * Constructor for using the output stream in polling mode.
     * @param[in] writer_ The USART writer for transmitting data.
     */

    UsartOutputStream::UsartOutputStream(UsartPollingWriter& writer_) :
        _writer(writer_) {
    }

    /*
     * Write one byte
     */

    bool UsartOutputStream::write(uint8_t c_) {
        _writer.send(c_);
        return true;
    }

    /*
     * Write many bytes
     */

    bool UsartOutputStream::write(const void *buffer_,uint32_t size_) {

        const uint8_t *ptr;

        ptr=static_cast<const uint8_t *>(buffer_);

        while(size_--)
            _writer.send(*ptr++);

        return true;
    }
}
