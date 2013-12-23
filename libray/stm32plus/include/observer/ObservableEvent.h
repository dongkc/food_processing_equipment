/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

namespace stm32plus {

    namespace ObservableEvent {

    /**
     * The observable events
     */

        enum E {
            /// A DMA transfer has completed OK
            DMA_TransferComplete,

            /// A DMA transfer is halfway complete
            DMA_HalfTransfer,

            /// There was an error during a DMA transfer
            DMA_TransferError,

            /// USART receive data
            USART_Receive,

            /// USART pre-transmit data
            USART_ReadyToTransmit,

            /// SPI receive data
            SPI_Receive,

            /// SPI pre-transmit data
            SPI_ReadyToTransmit,

            /// RTC tick event
            RTC_Tick,

            /// RTC alarm event
            RTC_Alarm,

            /// RTC overflow event
            RTC_Overflow,

            /// Touch panel event
            TouchPanel_ReadyForSampling,

            /// External interrupt has triggered
            EXTI_Triggered,

            /// Timer events
            Timer_Break,
            Timer_Compare,
            Timer_Update,
            Timer_Trigger,

            // Timeline update event
            Timeline_Update
        };
    }
}
