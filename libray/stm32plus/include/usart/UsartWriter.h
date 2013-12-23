/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "UsartBase.h"

namespace stm32plus {

    /**
     * @brief Base class for USART writers
     */

    class UsartWriter : public UsartBase {

        protected:
            UsartWriter(const UsartPeripheral& usart_)
                : UsartBase(usart_) {
            }

        public:

            /**
             * Virtual destructor, does nothing
             */

            virtual ~UsartWriter() {
            }

            /**
             * Check if ready to send.
             * @return true if the peripheral is ready to send data.
             */

            bool readyToSend() const {
                return USART_GetFlagStatus(_usart,USART_FLAG_TXE) == SET;
            }
    };
}
