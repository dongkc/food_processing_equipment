/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#include "spi/SpiDmaSyncWriter.h"


namespace stm32plus {

    /**
     * Constructor. Set up the DMA channel to write to the SPI, but leave the source address
     * unset so that the write() method can be repeatedly called
     *
     * @param[in] peripheral The SPI to write to
     * @param[in] priority The priority for this transfer.
     * @param[in] interruptFlags The DMA interrupt flags (e.g. DMA_IT_TC) that will be enabled, or 0 if none.
     */

    SpiDmaSyncWriter::SpiDmaSyncWriter(SpiPeripheral& peripheral,uint32_t priority,uint32_t interruptFlags)
        : SpiDmaWriter(peripheral,priority,interruptFlags) {

    }


    /**
     * @copydoc SpiDmaWriter::write
     */

    bool SpiDmaSyncWriter::write(uint8_t *dataToSend,uint32_t numBytes,uint8_t *dataReceived) {

        // call the base class to start the DMA write

        if(!SpiDmaWriter::write(dataToSend,numBytes,dataReceived))
            return false;

        // wait for it to complete

        return Dma::waitUntilComplete();
    }
}
