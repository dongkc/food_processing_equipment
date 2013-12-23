/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "dma/Dma.h"

namespace stm32plus {

    /**
     * @brief DMA memory to memory copier.
     *
     * Implements the memory-to-memory DMA copying facility.
     */

    class DmaMemoryCopy : public Dma {

        public:
            DmaMemoryCopy(
                    DMA_Channel_TypeDef *channel_,
                    uint32_t dataSize=DMA_MemoryDataSize_Byte,
                    uint32_t priority=DMA_Priority_High,
                    uint32_t interrupts_=0);

            void start(void *dest_,void *source_,uint32_t wordCount_);
    };

}
