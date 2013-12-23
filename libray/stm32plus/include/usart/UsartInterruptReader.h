/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "UsartReader.h"
#include "nvic/Nvic.h"
#include "observer/Observable.h"


namespace stm32plus {

    /**
     * @brief Interrupt-based USART reader.
     */

    class UsartInterruptReader : public UsartReader,
                                                             public Observable {

        public:

            /**
             * Structure that holds the data when a USART receive interrupt is processed
             */

            struct UsartReceiveEvent {
                /// The data received.
                uint8_t data;
            };

            // addresses of the up-to five usart interrupt readers
            static UsartInterruptReader *_usartInterruptReaders[5];

        public:

            /**
             * Constructor
             * @param[in] usart_ The USART peripheral that will be used.
             */

            UsartInterruptReader(const UsartPeripheral& usart_)
                : UsartReader(usart_) {

                // remember our address
                _usartInterruptReaders[usart_.getPeripheralIndex()]=this;

                // initialise the controller
                Nvic::configureIrq(usart_.getIrq());
            }

            /**
             * Virtual destructor, disables RX interrupts
             */

            virtual ~UsartInterruptReader() {
                USART_ITConfig(_usart,USART_IT_RXNE,DISABLE);
            }

            /**
             * Enable the receive interrupt.
             */

            void enableInterrupt() const {
                USART_ITConfig(_usart,USART_IT_RXNE,ENABLE);
            }

            /**
             * Disable the receive interrupt.
             */

            void disableInterrupt() const {
                USART_ITConfig(_usart,USART_IT_RXNE,DISABLE);
            }
    };
}
