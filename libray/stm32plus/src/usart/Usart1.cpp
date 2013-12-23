/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include <cstdlib>
#include "usart/Usart1.h"
#include "gpio/GpioPort.h"
#include "observer/ObservableEvent.h"
#include "config/interrupts.h"

namespace stm32plus {

    /**
     * Initialise the peripheral. The parameters to this function match those for USART_InitTypeDef
     *
     * @param[in] baudRate The standard baud rate to use.
     * @param[in] wordLength The word length to use.
     * @param[in] parity The parity setting.
     * @param[in] stopBits The number of stop bits.
     * @param[in] flowControl The flow control mode.
     * @param[in] mode The transmit/receive mode.
     */

    Usart1::Usart1(
            uint32_t baudRate,
            uint16_t wordLength,
            uint16_t parity,
            uint16_t stopBits,
            uint16_t flowControl,
            uint16_t mode) : UsartPeripheral(USART1,DMA1_Channel4,DMA1_Channel5,0,USART1_IRQn) {

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO,ENABLE);

        GpioPort pa(GPIOA);
        pa.initialise(GPIO_Speed_50MHz,GPIO_Mode_AF_PP,GPIO_Pin_TX); // TX
        pa.initialise(GPIO_Speed_50MHz,GPIO_Mode_IN_FLOATING,GPIO_Pin_RX); // RX

        initialisePeripheral(baudRate,wordLength,parity,stopBits,flowControl,mode);
    }

}

