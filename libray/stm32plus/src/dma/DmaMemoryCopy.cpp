/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "dma/DmaMemoryCopy.h"


namespace stm32plus {

    /**
     * Constructor. Set up the DMA channel to memory, but leave the addresses
     * and data size unset so that the start() method can be repeatedly called.
     *
     * @param[in] channel_ The DMA channel to use for this transfer
     * @param[in] dataSize_ The size of a single word in bytes, e.g. 4 to transfer units of 32-bits. Must be 4, 2 or 1.
     * @param[in] priority_ The DMA channel priority.
     * @param[in] interrupts_ If we are using interrupts, these are the flags to enable.
     */

    DmaMemoryCopy::DmaMemoryCopy(DMA_Channel_TypeDef *channel_,uint32_t dataSize_,uint32_t priority_,uint32_t interrupts_) :
        Dma(channel_,interrupts_) {

        uint32_t periphDataSize;

        if(dataSize_==DMA_MemoryDataSize_Byte)
            periphDataSize=DMA_PeripheralDataSize_Byte;
        else if(dataSize_==DMA_MemoryDataSize_HalfWord)
            periphDataSize=DMA_PeripheralDataSize_HalfWord;
        else
            periphDataSize=DMA_PeripheralDataSize_Word;

        DMA_DIR=DMA_DIR_PeripheralSRC;                                            // 'peripheral' is source
        DMA_PeripheralInc=DMA_PeripheralInc_Enable;                    // 'peripheral' gets incremented
        DMA_MemoryInc=DMA_MemoryInc_Enable;                                    // memory is incremented
        DMA_PeripheralDataSize=periphDataSize;                            // user defined word size
        DMA_MemoryDataSize=dataSize_;                                                // user defined word size
        DMA_Mode=DMA_Mode_Normal;                                                        // not a circular buffer
        DMA_Priority=priority_;                                                            // user-configurable priority
        DMA_M2M=DMA_M2M_Enable;                                                            // memory->memory configuration
    }

    /**
     * Start a transfer of data from source_ to the dest_. The count is in units
     * of the word size.
     *
     * @param[in] dest_ The destination of the transfer.
     * @param[in] source_ The source of the transfer.
     * @param[in] count_ The number of words to transfer.
     */

    void DmaMemoryCopy::start(void *dest_,void *source_,uint32_t count_) {

        DMA_PeripheralBaseAddr=reinterpret_cast<uint32_t> (source_);
        DMA_MemoryBaseAddr=reinterpret_cast<uint32_t> (dest_);
        DMA_BufferSize=count_;

        Dma::start();
    }
}
