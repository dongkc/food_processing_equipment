/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "dma/Dma.h"
#include "usart/UsartReader.h"


namespace stm32plus {

    /**
     * @brief Class to transfer data from a USART using the DMA channel.
     *
     * Using DMA to transfer a block of data from the USART can free up the CPU to
     * do other things while an asynchronous transfer takes place.
     */

    class UsartDmaReader : public UsartReader,
                                                 public Dma {

        public:

        /**
         * Constructor. Set up the DMA channel to copy from the USART, but leave the source address
         * and data size unset so that the start() method can be repeatedly called.
         *
         * @param[in] usart_ The USART to copy from.
         * @param[in] priority_ The priority for this transfer.#
         * @param[in] interruptFlags_ The DMA interrupt flags (e.g. DMA_IT_TC) that will be enabled, or 0 if none.
         */

            UsartDmaReader(const UsartPeripheral& usart_,uint32_t priority_=DMA_Priority_High,uint32_t interruptFlags_=0)
                : UsartReader(usart_),
                  Dma(usart_.getReceiveChannel(),interruptFlags_) {

                DMA_PeripheralBaseAddr=reinterpret_cast<uint32_t>(&usart_.getPeripheralAddress()->DR);
                DMA_DIR=DMA_DIR_PeripheralSRC;                                            // 'peripheral' is source
                DMA_PeripheralInc=DMA_PeripheralInc_Disable;                // 'peripheral' does not increment
                DMA_MemoryInc=DMA_MemoryInc_Enable;                                    // memory is incremented
                DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;    // transferring bytes
                DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;                    // user defined word size
                DMA_Mode=DMA_Mode_Normal;                                                        // not a circular buffer
                DMA_Priority=priority_;                                                            // user-configurable priority
                DMA_M2M=DMA_M2M_Disable;                                                        // memory->peripheral configuration
            }


            /**
             * Start a transfer of data from the USART data register to dest_.
             *
             * @param[in] dest_
             *   memory address where the bytes will be written to
             * @param[in] count_
             *   The number of 8-bit bytes to transfer.
             */

            void receive(void *dest_,uint32_t count_) {

            // set up the parameters for this transfer

                DMA_MemoryBaseAddr=reinterpret_cast<uint32_t>(dest_);
                DMA_BufferSize=count_;

                USART_DMACmd(_usart.getPeripheralAddress(),USART_DMAReq_Rx,ENABLE);

            // disable and then re-enable

                Dma::start();
            }
    };
}
