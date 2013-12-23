/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */
#if 0

#include "config/interrupts.h"
#include "spi/SpiInterruptReader.h"
#include "spi/SpiInterruptWriter.h"

namespace stm32plus {

    /// pointers back to the singleton instance(s) of the interrupt writers that have been instantiated
    SpiInterruptWriter *SpiInterruptWriter::_spiInterruptWriters[3];

    /// pointers back to the singleton instance(s) of the interrupt readers that have been instantiated
    SpiInterruptReader *SpiInterruptReader::_spiInterruptReaders[3];
}


using namespace stm32plus;

extern "C" {

#if defined(USE_SPI1_INTERRUPT) || \
        defined(USE_SPI2_INTERRUPT) || \
        defined(USE_SPI3_INTERRUPT)


    static void handleSpiInterrupt(SPI_TypeDef *whichOne_,SpiInterruptReader *reader_,SpiInterruptWriter *writer_) {

        if(SPI_I2S_GetITStatus(whichOne_,SPI_I2S_IT_RXNE) != RESET) {

            // read the available byte into the event

            SpiInterruptReader::SpiReceiveEvent event;

            event.data=SPI_I2S_ReceiveData(whichOne_);

            reader_->notifyObservers(ObservableEvent::SPI_Receive,&event);
            SPI_I2S_ClearITPendingBit(whichOne_,SPI_I2S_IT_RXNE);
        }

        if(SPI_I2S_GetITStatus(whichOne_,SPI_I2S_IT_TXE) != RESET)
            writer_->notifyObservers(ObservableEvent::SPI_ReadyToTransmit);
    }

#endif
#if defined(USE_SPI1_INTERRUPT)

    void SPI1_IRQHandler(void) {
        handleSpiInterrupt(SPI1,SpiInterruptReader::_spiInterruptReaders[0],SpiInterruptWriter::_spiInterruptWriters[0]);
    }

#endif
#if defined(USE_SPI2_INTERRUPT)

    void SPI2_IRQHandler(void) {
        handleSpiInterrupt(SPI2,SpiInterruptReader::_spiInterruptReaders[1],SpiInterruptWriter::_spiInterruptWriters[1]);
    }

#endif
#if defined(USE_SPI3_INTERRUPT)

    void SPI3_IRQHandler(void) {
        handleSpiInterrupt(SPI3,SpiInterruptReader::_spiInterruptReaders[2],SpiInterruptWriter::_spiInterruptWriters[2]);
    }

#endif

} // extern "C"

#endif
