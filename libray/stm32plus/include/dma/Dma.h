/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include <stdint.h>
#include "config/stdperiph.h"
#include "observer/Observable.h"
#include "nvic/Nvic.h"

namespace stm32plus {

    /**
     * @brief Base class for DMA subclasses.
     *
     * Derives from DMA_InitTypeDef so can be
     * directly customised by the caller
     */

    class Dma : public DMA_InitTypeDef,
                            public Observable {

        public:

            /**
             * Context structure for Dma observers to look at.
             */

            struct InterruptEvent {
                    /// Pointer to the DMA class
                    Dma *dma;

                    /// The interrupt flag that was triggered
                    uint32_t interruptFlag;
            };

            /**
             * Static pointers to the handlers for DMA channel 1. These are used by
             * the interrupt handlers to get back into the OO system.
             */

            static Dma *Dma1_ChannelHandlers[7];

            /**
             * Static pointers to the handlers for DMA channel 2. These are used by
             * the interrupt handlers to get back into the OO system.
             */

            static Dma *Dma2_ChannelHandlers[5];

            /**
             * Error codes
             */

            enum {
                /// Transfer error
                E_TRANSFER_ERROR=1
            };

        protected:

            DMA_Channel_TypeDef *_channel;
            uint8_t _dmaPeripheral;
            uint8_t _channelIndex;
            uint8_t _nvic;
            uint32_t _interruptFlags;

        protected:
            Dma(DMA_Channel_TypeDef *channel_,uint32_t interruptFlags_=0);
            ~Dma();

            void setPeripheral();
            void start();
            void enableInterrupts(uint32_t interruptFlags_);

        public:
            bool waitUntilComplete() const;
            uint32_t getTransferCompleteFlag() const;
            uint32_t getTransferErrorFlag() const;
    };
}
