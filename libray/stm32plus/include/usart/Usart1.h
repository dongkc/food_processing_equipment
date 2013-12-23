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
     * @brief Usart1 implementation
     */

    class Usart1 : public UsartPeripheral {
        public:
            /// The transmit pin
            static const uint16_t GPIO_Pin_TX=GPIO_Pin_9;

            /// The receive pin
            static const uint16_t GPIO_Pin_RX=GPIO_Pin_10;

            /*
             * Constructor
             */

            Usart1(
                    uint32_t baudRate,
                    uint16_t wordLength_=USART_WordLength_8b,
                    uint16_t parity=USART_Parity_No,
                    uint16_t stopBits=USART_StopBits_1,
                    uint16_t flowControl=USART_HardwareFlowControl_None,
                    uint16_t mode=USART_Mode_Rx | USART_Mode_Tx
                );
    };

}

