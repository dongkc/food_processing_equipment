/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "UsartReader.h"


namespace stm32plus {

    /**
     * @brief USART class for synchronous reading.
     *
     * Synchronous reading blocks until data is available.
     */

    class UsartPollingReader : public UsartReader {
        public:


        /**
         * Constructor
         * @param[in] usart_ The USART peripheral that will be used
         */

            UsartPollingReader(const UsartPeripheral& usart_)
                : UsartReader(usart_) {
            }

            /**
             * Virtual destructor, does nothing
             */

            virtual ~UsartPollingReader() {
            }

            /**
             * Receive a byte, blocking.
             * @return The byte, or 0xff if it failed. Of course the data byte itself may be 0xff. The caller should check
             *  the error provider to see if the 0xff is indicating an error or a data byte.
             */

            uint8_t receive() const {

                uint32_t errorCode;

                do {
                    if(hasError(errorCode))
                        return 0xff; // caller to check global error status

                } while(!dataAvailable());

                return USART_ReceiveData(_usart) & 0xff;
            }

    };
}
