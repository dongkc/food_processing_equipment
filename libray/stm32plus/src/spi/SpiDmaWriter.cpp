/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "spi/SpiDmaWriter.h"


namespace stm32plus {


    /**
     * Constructor. Set up the DMA channel to write to the SPI, but leave the source address
     * unset so that the write() method can be repeatedly called
     *
     * @param[in] peripheral The SPI to write to
     * @param[in] priority The priority for this transfer.
     * @param[in] interruptFlags The DMA interrupt flags (e.g. DMA_IT_TC) that will be enabled, or 0 if none.
     */

    SpiDmaWriter::SpiDmaWriter(SpiPeripheral& peripheral,uint32_t priority,uint32_t interruptFlags)
        : SpiWriter(peripheral),
          Dma(peripheral.getTransmitChannel(),interruptFlags) {

        DMA_PeripheralBaseAddr=reinterpret_cast<uint32_t>(&peripheral.getPeripheralAddress()->DR);
        DMA_DIR=DMA_DIR_PeripheralDST;                                            // 'peripheral' is destination
        DMA_PeripheralInc=DMA_PeripheralInc_Disable;                // 'peripheral' does not increment
        DMA_MemoryInc=DMA_MemoryInc_Enable;                                    // memory is incremented
        DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;    // transferring bytes
        DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;                    // user defined word size
        DMA_Mode=DMA_Mode_Normal;                                                        // not a circular buffer
        DMA_Priority=priority;                                                            // user-configurable priority
        DMA_M2M=DMA_M2M_Disable;                                                        // memory->peripheral configuration
    }


    /**
     * Start writing a block of bytes, full duplex receiving at the same time is not supported.
     * The DMA transfer is started and will run asynchronously.
     * @param[in] dataToSend The bytes to transmit.
     * @param[in] dataReceived Where to store the output bytes, or NULL if you're not interested in it or this peripheral is not running in duplex mode.
     * @param[in] numBytes the number of bytes to send (and maybe receive)
     * @return false if it fails.
     */

    bool SpiDmaWriter::write(
            uint8_t *dataToSend,
            uint32_t numBytes,
            uint8_t *dataReceived  __attribute__((unused))) {

        // set up the parameters for this transfer

        DMA_MemoryBaseAddr=reinterpret_cast<uint32_t>(dataToSend);
        DMA_BufferSize=numBytes;

        // disable and then re-enable

        Dma::start();

        // finally let it go

        SPI_I2S_DMACmd(_peripheral.getPeripheralAddress(),SPI_I2S_DMAReq_Tx,ENABLE);
        return true;
    }
}
