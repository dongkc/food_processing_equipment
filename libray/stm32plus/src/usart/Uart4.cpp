/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include <cstdlib>
#include "usart/Uart4.h"
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

    Uart4::Uart4(
            uint32_t baudRate_,
            uint16_t wordLength_,
            uint16_t parity_,
            uint16_t stopBits_,
            uint16_t flowControl_,
            uint16_t mode_) : UsartPeripheral(UART4,DMA2_Channel5,DMA2_Channel3,3,UART4_IRQn) {

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);

        GpioPort pc(GPIOC);
        pc.initialise(GPIO_Speed_50MHz,GPIO_Mode_AF_PP,GPIO_Pin_TX);                 // TX
        pc.initialise(GPIO_Speed_50MHz,GPIO_Mode_IN_FLOATING,GPIO_Pin_RX);     // RX

        initialisePeripheral(baudRate_,wordLength_,parity_,stopBits_,flowControl_,mode_);
    }
}
