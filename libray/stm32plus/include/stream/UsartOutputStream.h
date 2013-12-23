/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "usart/UsartPollingWriter.h"
#include "stream/OutputStream.h"

namespace stm32plus {

    /**
     * @brief Implementation of an output stream for the serial USART.
     *
     * Writing to this stream causes data to be transmitted to the USART.
     */

    class UsartOutputStream : public OutputStream {

        protected:
            UsartPollingWriter& _writer;

        public:
            UsartOutputStream(UsartPollingWriter& usart_);

            virtual ~UsartOutputStream() {
            }

            // overrides from OutputStream

            virtual bool write(uint8_t c_);
            virtual bool write(const void *buffer,uint32_t size_);

            /**
             * Always true.
             * @return always true
             */

            virtual bool flush() {
                return true;
            }

            /**
             * Always true.
             * @return always true
             */

            virtual bool close() {
                return true;
            }
    };
}
