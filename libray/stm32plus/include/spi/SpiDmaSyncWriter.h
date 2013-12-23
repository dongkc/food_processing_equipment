/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once


#include "spi/SpiDmaWriter.h"


namespace stm32plus {


    /**
     * @brief Synchronous DMA writer to SPI peripherals.
     *
     * Extends SpiDmaWriter and adds a call to Dma::waitUntilComplete after writing
     */

    class SpiDmaSyncWriter : public SpiDmaWriter {

        public:
            SpiDmaSyncWriter(SpiPeripheral& peripheral,uint32_t priority=DMA_Priority_High,uint32_t interruptFlags=0);
            virtual ~SpiDmaSyncWriter() {}

            // overrides from SpiDmaWriter
            virtual bool write(uint8_t *dataToSend,uint32_t numBytes,uint8_t *dataReceived=NULL);
    };
}
