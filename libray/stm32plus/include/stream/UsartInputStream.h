/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "usart/UsartPollingReader.h"
#include "stream/InputStream.h"

namespace stm32plus {

    /**
     * @brief Implementation of an input stream for the serial USART.
     *
     * The stream methods can be used to read data from the USART in polling mode
     */

    class UsartInputStream : public InputStream {

        protected:
            UsartPollingReader& _reader;

        public:

            /**
             * Constructor in polling mode.
             * @param[in] reader The polling reader that will be used as the data source.
             */

            UsartInputStream(UsartPollingReader& reader);

            virtual ~UsartInputStream() {
            }

            // overrides from InputStream

            virtual int16_t read();
            virtual bool read(void *buffer,uint32_t size,uint32_t& actuallyRead);
            virtual bool skip(uint32_t howMuch);
            virtual bool available();


            /**
             * Doesn't do anything.
             * @return always true
             */

            virtual bool close() {
                return true;
            }


            /**
             * Not supported.
             * @return always false and E_OPERATION_NOT_SUPPORTED
             */

            virtual bool reset() {
                return errorProvider.set(ErrorProvider::ERROR_PROVIDER_USART_INPUT_STREAM,E_OPERATION_NOT_SUPPORTED);
            }
    };
}
