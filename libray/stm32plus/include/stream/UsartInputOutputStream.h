/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "usart/UsartBase.h"
#include "stream/UsartInputStream.h"
#include "stream/UsartOutputStream.h"

namespace stm32plus {

    /**
     * @brief Implementation of an input/output stream for the serial usart.
     *
     * This class encapsulates a UsartInputStream and a UsartOutputStream to give easy
     * stream based read/write access to a USART.
     */

    class UsartInputOutputStream : public InputStream,public OutputStream {

        protected:
            UsartInputStream _inputStream;
            UsartOutputStream _outputStream;

        public:

            /**
             * Constructor for using the USART in polling mode.
             * @param[in] usart The USART to read/write.
             */

            UsartInputOutputStream(const Usart& usart) :
                _inputStream(usart), _outputStream(usart) {
            }


            /**
             * Constructor for using the USART in interrupt mode.
             * @param[in] usart The USART that is being used.
             * @param[in] is The input stream that supplies data for transmitting to the USART.
             * @param[in] os The output stream that collects data received by the USART.
             */

            UsartInputOutputStream(const Usart& usart,InputStream& is,OutputStream& os) :
                _inputStream(usart,os), _outputStream(usart,is) {
            }


            /**
             * Virtual destructor, do nothing.
             */

            virtual ~UsartInputOutputStream() {
            }

            /**
             * @copydoc InputStream::read
             */

            virtual int16_t read() {
                return _inputStream.read();
            }

            /**
             * @copydoc InputStream::read
             */

            virtual bool read(void *buffer,uint32_t size,uint32_t& actuallyRead) {
                return _inputStream.read(buffer,size,actuallyRead);
            }

            /**
             * @copydoc InputStream::skip
             */

            virtual bool skip(uint32_t howMuch) {
                return _inputStream.skip(howMuch);
            }

            /**
             * @copydoc InputStream::available
             */

            virtual bool available() {
                return _inputStream.available();
            }

            // overrides from OutputStream

            virtual bool write(uint8_t c) {
                return _outputStream.write(c);
            }

            virtual bool write(const void *buffer,uint32_t size) {
                return _outputStream.write(buffer,size);
            }

            // common overrides from InputStream and OutputStream

            virtual bool close() {
                return false;
            }
    };
}
