/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#include "display/graphic/DmaFsmcLcdMemoryCopy.h"


namespace stm32plus {
    namespace display {

        /**
         * Constructor. Set up the DMA channel to copy to the LCD, but leave the source address
         * and data size unset so that the start() method can be repeatedly called.
         *
         * @param[in] channel The DMA channel to use.
         * @param[in] dataAddress The FSMC address used to transfer data
         * @param[in] busWidthInBytes The width of the FSMC bus, in bytes.
         * @param[in] priority The priority for this transfer.
         * @param[in] interrupts If there is an observer then these are the interrupts that we are observing.
         */

        DmaFsmcLcdMemoryCopy::DmaFsmcLcdMemoryCopy(
                DMA_Channel_TypeDef *channel,
                const volatile void *dataAddress,
                uint16_t busWidthInBytes,
                uint32_t priority,
                uint32_t interrupts) : Dma(channel,interrupts) {

            DMA_MemoryBaseAddr=reinterpret_cast<uint32_t>(dataAddress);                // memory target is the FSMC
            DMA_DIR=DMA_DIR_PeripheralSRC;                                                                        // 'peripheral' is source
            DMA_PeripheralInc=DMA_PeripheralInc_Enable;                                                // 'peripheral' gets incremented
            DMA_MemoryInc=DMA_MemoryInc_Disable;                                                            // LCD register is not incremented
            DMA_Mode=DMA_Mode_Normal;                                                                                    // not a circular buffer
            DMA_Priority=priority;                                                                                        // user-configurable priority
            DMA_M2M=DMA_M2M_Enable;                                                                                        // memory->memory configuration

            // set up the bus width in bytes

            _busWidthInBytes=busWidthInBytes;

            // the constants for the memory/peripheral sizes are different!!

            DMA_MemoryDataSize=busWidthInBytes==1 ? DMA_MemoryDataSize_Byte :
                                                         busWidthInBytes==2 ? DMA_MemoryDataSize_HalfWord : DMA_MemoryDataSize_Word;

            DMA_PeripheralDataSize=busWidthInBytes==1 ? DMA_PeripheralDataSize_Byte :
                                                         busWidthInBytes==2 ? DMA_PeripheralDataSize_HalfWord : DMA_PeripheralDataSize_Word;
        }

        /**
         * Start a transfer of data from source to the LCD data register.
         *
         * @param[in] source
         *   memory address of the source data. Must be word-aligned. The data is arranged as a
         *   sequence of words.
         * @param[in] byteCount
         *   The number of bytes to transfer.
         */

        void DmaFsmcLcdMemoryCopy::start(void *source,uint32_t byteCount) {

            DMA_PeripheralBaseAddr=reinterpret_cast<uint32_t>(source);
            DMA_BufferSize=byteCount/_busWidthInBytes;

            Dma::start();
        }
    }
}
