/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once


#include "UsartWriter.h"
#include "observer/Observable.h"
#include "nvic/Nvic.h"

namespace stm32plus {


    /**
     * @brief interrupt based USART writer.
     */

    class UsartInterruptWriter : public UsartWriter, public Observable {

        public:

            static UsartInterruptWriter *_usartInterruptWriters[5];

        public:

            /**
             * Constructor
             * @param[in] usart_ The USART peripheral that will be used.
             */

            UsartInterruptWriter(const UsartPeripheral& usart_)
                : UsartWriter(usart_) {

                // remember our address
                _usartInterruptWriters[usart_.getPeripheralIndex()]=this;

                // initialise the controller
                Nvic::configureIrq(usart_.getIrq());
            }

            /**
             * Virtual destructor, disables TX interrupts
             */

            virtual ~UsartInterruptWriter() {
                USART_ITConfig(_usart,USART_IT_TXE,DISABLE);
            }

            /**
             * Enable the TX interrupt.
             */

            void enableInterrupt() const {
                USART_ITConfig(_usart,USART_IT_TXE,ENABLE);
            }

            /**
             * Disable the TX interrupt.
             */

            void disableInterrupt() const {
                USART_ITConfig(_usart,USART_IT_TXE,DISABLE);
            }

    };
}
