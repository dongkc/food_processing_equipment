/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once


#include "UsartBase.h"


namespace stm32plus {


    /**
     * Base class for USART readers
     */

    class UsartReader : public UsartBase {

        protected:

        /**
         * Constructor
         * @param[in] usart_ The USART peripheral that will be used
         */

            UsartReader(const UsartPeripheral& usart_)
                : UsartBase(usart_) {
            }

        public:

            /**
             * Virtual destructor, does nothing
             */

            virtual ~UsartReader() {
            }

            /**
             * Check if there is data available.
             * @return true if there is data available.
             */

            bool dataAvailable() const {
                return USART_GetFlagStatus(_usart,USART_FLAG_RXNE) == SET;
            }
    };
}
