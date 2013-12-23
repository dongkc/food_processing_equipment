/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "config/interrupts.h"
#include "usart/UsartInterruptReader.h"
#include "usart/UsartInterruptWriter.h"

namespace stm32plus {

    /// pointers back to the singleton instance(s) of the interrupt writers that have been instantiated
    UsartInterruptWriter *UsartInterruptWriter::_usartInterruptWriters[5];

    /// pointers back to the singleton instance(s) of the interrupt readers that have been instantiated
    UsartInterruptReader *UsartInterruptReader::_usartInterruptReaders[5];
}


using namespace stm32plus;

extern "C" {

#if defined(USE_USART1_INTERRUPT) || \
        defined(USE_USART2_INTERRUPT) || \
        defined(USE_USART3_INTERRUPT) || \
        defined(USE_UART4_INTERRUPT) || \
        defined(USE_UART5_INTERRUPT)


    static void handleUsartInterrupt(USART_TypeDef *whichOne_,UsartInterruptReader *reader_,UsartInterruptWriter *writer_) {

        if(USART_GetITStatus(whichOne_,USART_IT_RXNE) != RESET) {

            USART_ClearITPendingBit(whichOne_,USART_IT_RXNE);

            // read the available byte into the event

            UsartInterruptReader::UsartReceiveEvent event;

            event.data=USART_ReceiveData(whichOne_);
            reader_->notifyObservers(ObservableEvent::USART_Receive,&event);
        }

        if(USART_GetITStatus(whichOne_,USART_IT_TXE) != RESET) {

            USART_ClearITPendingBit(whichOne_,USART_IT_TXE);

            writer_->notifyObservers(
                    ObservableEvent::USART_ReadyToTransmit
            );
        }
    }

#endif
#if defined(USE_USART1_INTERRUPT)

    void USART1_IRQHandler(void) {
        handleUsartInterrupt(USART1,UsartInterruptReader::_usartInterruptReaders[0],UsartInterruptWriter::_usartInterruptWriters[0]);
    }

#endif
#if defined(USE_USART2_INTERRUPT)

    void USART2_IRQHandler(void) {
        handleUsartInterrupt(USART2,UsartInterruptReader::_usartInterruptReaders[1],UsartInterruptWriter::_usartInterruptWriters[1]);
    }

#endif
#if defined(USE_USART3_INTERRUPT)

    void USART3_IRQHandler(void) {
        handleUsartInterrupt(USART3,UsartInterruptReader::_usartInterruptReaders[2],UsartInterruptWriter::_usartInterruptWriters[2]);
    }

#endif
#if defined(USE_UART4_INTERRUPT)

    void USART4_IRQHandler(void) {
        handleUsartInterrupt(UART4,UsartInterruptReader::_usartInterruptReaders[3],UsartInterruptWriter::_usartInterruptWriters[3]);
    }

#endif
#if defined(USE_UART5_INTERRUPT)

    void USART5_IRQHandler(void) {
        handleUsartInterrupt(UART5,UsartInterruptReader::_usartInterruptReaders[4],UsartInterruptWriter::_usartInterruptWriters[4]);
    }

#endif

} // extern "C"
