/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "UsartWriter.h"


namespace stm32plus {

    /**
     * @brief Synchronous writer for USART peripherals.
     *
     * Synchronous writing blocks the caller until data is sent.
     */

    class UsartPollingWriter : public UsartWriter {
        public:

        /**
         * Constructor
         * @param[in] usart_ The USART peripheral that will be used.
         */

            UsartPollingWriter(const UsartPeripheral& usart_)
                : UsartWriter(usart_) {
            }


            /**
             * Virtual destructor, does nothing
             */

            virtual ~UsartPollingWriter() {
            }

            /**
             * Send a byte and wait until it's gone
             * @param byte_ The byte to send.
             * @return false if it failed.
             */

            bool send(uint8_t byte_) const {

                uint32_t errorCode;

                do {
                    if(hasError(errorCode))
                        return false;

                } while(!readyToSend());

                USART_SendData(_usart,byte_);
                return true;
            }


    };
}
