/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include <cstdlib>
#include "usart/Usart3.h"
#include "gpio/GpioPort.h"
#include "nvic/Nvic.h"
#include "config/interrupts.h"

namespace stm32plus {

    /**
     * Initialise the peripheral. The parameters to this function match those for USART_InitTypeDef
     *
     * @param[in] baudRate_ The standard baud rate to use.
     * @param[in] wordLength_ The word length to use.
     * @param[in] parity_ The parity setting.
     * @param[in] stopBits_ The number of stop bits.
     * @param[in] flowControl_ The flow control mode.
     * @param[in] mode_ The transmit/receive mode.
     */

    Usart3::Usart3(
            uint32_t baudRate_,
            uint16_t wordLength_,
            uint16_t parity_,
            uint16_t stopBits_,
            uint16_t flowControl_,
            uint16_t mode_) : UsartPeripheral(USART3,DMA1_Channel2,DMA1_Channel3,2,USART3_IRQn) {

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);

        GpioPort pb(GPIOB);
        pb.initialise(GPIO_Speed_50MHz,GPIO_Mode_AF_PP,GPIO_Pin_TX);                 // TX
        pb.initialise(GPIO_Speed_50MHz,GPIO_Mode_IN_FLOATING,GPIO_Pin_RX);     // RX

        initialisePeripheral(baudRate_,wordLength_,parity_,stopBits_,flowControl_,mode_);
    }
}

