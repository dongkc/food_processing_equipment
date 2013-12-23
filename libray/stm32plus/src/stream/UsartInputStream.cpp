/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "stream/UsartInputStream.h"
#include "error/ErrorProvider.h"

namespace stm32plus {

    /*
     * Constructor
     */

    UsartInputStream::UsartInputStream(UsartPollingReader& reader) :
        _reader(reader) {
    }


    /*
     * Read a byte
     */

    int16_t UsartInputStream::read() {

        uint8_t data;

        if((data=_reader.receive())==0xff && errorProvider.getLast()!=ErrorProvider::ERROR_NO_ERROR)
            return E_STREAM_ERROR;

        return data;
    }

    /*
     * Read many bytes
     */

    bool UsartInputStream::read(void *buffer,uint32_t size,uint32_t& actuallyRead) {

        uint8_t *ptr;
        int16_t data;

        ptr=static_cast<uint8_t *> (buffer);
        actuallyRead=size;

        while(size--) {

            if((data=read())==E_STREAM_ERROR)
                return false;

            *ptr++=data;
        }

        return true;
    }


    /*
     * Cannot skip
     */

    bool UsartInputStream::skip(uint32_t howMuch __attribute__((unused))) {
        return errorProvider.set(ErrorProvider::ERROR_PROVIDER_INPUT_STREAM,E_OPERATION_NOT_SUPPORTED);
    }


    /*
     * Check if data is available
     */

    bool UsartInputStream::available() {
        return _reader.dataAvailable();
    }
}
