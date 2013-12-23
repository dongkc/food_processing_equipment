/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "spi/SpiWriter.h"
#include "dma/Dma.h"


namespace stm32plus {

    /**
     * @brief Implementation of a SPI writer that uses the DMA channel
     *
     * Using the DMA channel for bulk-writes to the SPI peripheral.
     */

    class SpiDmaWriter : public SpiWriter,
                                             public Dma {

      public:
            SpiDmaWriter(SpiPeripheral& peripheral,uint32_t priority=DMA_Priority_High,uint32_t interruptFlags=0);
            virtual ~SpiDmaWriter() {}

            // overrides from SpiWriter
            virtual bool write(uint8_t *dataToSend,uint32_t numBytes,uint8_t *dataReceived=NULL);
    };
}
