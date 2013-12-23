/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "dma/Dma.h"



namespace stm32plus {
    namespace display {


        /**
         * @brief Copy data to an LCD display connected via an 8080 interface.
         *
         * Custom DMA configuration to bulk copy data into the lcd data register
         * through the FSMC. This can free the CPU to do other things while data
         * is transferred to the display.
         */

        class DmaFsmcLcdMemoryCopy : public Dma {

            protected:
                uint16_t _busWidthInBytes;            // we'll use this to scale down a byte count

            public:

                DmaFsmcLcdMemoryCopy(
                        DMA_Channel_TypeDef *channel,
                        const volatile void *dataAddress,
                        uint16_t busWidthInBytes,
                        uint32_t priority=DMA_Priority_High,
                        uint32_t interrupts=0
                    );

                void start(void *source,uint32_t byteCount);
        };
    }
}
