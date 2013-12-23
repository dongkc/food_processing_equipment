/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "stream/OutputStream.h"

namespace stm32plus {

    /**
     * Write a signed byte to the stream.
     * @param[in] c_ The byte to write.
     * @return A self reference to allow chaining of the operator.
     */

    OutputStream& OutputStream::operator<<(int8_t& c_) {
        return opWrite(&c_,sizeof(c_));
    }

    /**
     * Write a signed 16-bit integer to the stream.
     * @param[in] c_ The 16-bit integer to write.
     * @return A self reference to allow chaining of the operator.
     */

    OutputStream& OutputStream::operator<<(int16_t& c_) {
        return opWrite(&c_,sizeof(c_));
    }

    /**
     * Write a signed 32-bit integer to the stream.
     * @param[in] c_ The 32-bit integer to write.
     * @return A self reference to allow chaining of the operator.
     */

    OutputStream& OutputStream::operator<<(int32_t& c_) {
        return opWrite(&c_,sizeof(c_));
    }

    /**
     * Write an unsigned byte to the stream.
     * @param[in] c_ The byte to write.
     * @return A self reference to allow chaining of the operator.
     */

    OutputStream& OutputStream::operator<<(uint8_t& c_) {
        return opWrite(&c_,sizeof(c_));
    }

    /**
     * Write an unsigned 16-bit integer to the stream.
     * @param[in] c_ The 16-bit integer to write.
     * @return A self reference to allow chaining of the operator.
     */

    OutputStream& OutputStream::operator<<(uint16_t& c_) {
        return opWrite(&c_,sizeof(c_));
    }

    /**
     * Write an unsigned 32-bit integer to the stream.
     * @param[in] c_ The 32-bit integer to write.
     * @return A self reference to allow chaining of the operator.
     */

    OutputStream& OutputStream::operator<<(uint32_t& c_) {
        return opWrite(&c_,sizeof(c_));
    }

    /*
     * Write some data for one of the operators
     */

    OutputStream& OutputStream::opWrite(void *buffer_,uint32_t bufferSize_) {
        write(buffer_,bufferSize_);
        return *this;
    }
}
