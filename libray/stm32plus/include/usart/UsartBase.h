/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "config/stdperiph.h"
#include "usart/UsartPeripheral.h"
#include "error/ErrorProvider.h"


namespace stm32plus {

    /**
     * @brief Base class for USART operations.
     */

    class UsartBase {

        protected:
            const UsartPeripheral& _usart;

        public:
            /**
             * Error codes
             */

            enum {

                /// There was an error using the USART
                E_USART_ERROR=1
            };

        protected:

            /**
             * Constructor.
             * @param usart_ The USART peripheral that will be used for the operations.
             */

            UsartBase(const UsartPeripheral& usart_) :
                _usart(usart_) {
            }

        public:

            /**
             * Virtual destructor, does nothing.
             */

            virtual ~UsartBase() {
            }

            /**
             * check for an error state
             * @param[out] errorCode_ The peripheral error code (USART_FLAG_ORE, USART_FLAG_NE, USART_FLAG_FE,USART_FLAG_PE).
             * @return true if there was an error, false if no error.
             */

            bool hasError(uint32_t& errorCode_) const {
                errorCode_=USART_GetFlagStatus(_usart,USART_FLAG_ORE | USART_FLAG_NE | USART_FLAG_FE | USART_FLAG_PE);

                if(errorCode_) {
                    USART_ReceiveData( _usart); // required to clear error state
                    return !errorProvider.set(ErrorProvider::ERROR_PROVIDER_USART,E_USART_ERROR,errorCode_);
                }

                // no error

                return false;
            }


            /**
             * return a reference to the peripheral.
             * @return The peripheral
             */

            const UsartPeripheral& getUsartPeripheral() const {
                return _usart;
            }
    };
}
