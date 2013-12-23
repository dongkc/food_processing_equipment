/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "UsartPeripheral.h"
#include "config/stdperiph.h"

namespace stm32plus {

    /**
     * @brief Uart4 implementation
     */

    class Uart4 : public UsartPeripheral {

        /// The transmit pin
        static const uint16_t GPIO_Pin_TX=GPIO_Pin_10;

        /// The receive pin
        static const uint16_t GPIO_Pin_RX=GPIO_Pin_11;

        public:

            /*
             * Constructor
             */

            Uart4(
                    uint32_t baudRate_,
                    uint16_t wordLength_=USART_WordLength_8b,
                    uint16_t parity_=USART_Parity_No,
                    uint16_t stopBits_=USART_StopBits_1,
                    uint16_t flowControl=USART_HardwareFlowControl_None,
                    uint16_t mode_=USART_Mode_Rx | USART_Mode_Tx
                );
    };

}
