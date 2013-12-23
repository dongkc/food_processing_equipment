/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "dma/Dma.h"
#include "usart/UsartWriter.h"


namespace stm32plus {


    /**
     * Usart writer class that uses a DMA channel so that the CPU is free
     * to do other things
     */

    class UsartDmaWriter : public UsartWriter,
                                                 public Dma {

        public:

        /**
         * Constructor. Set up the DMA channel to copy to the USART, but leave the source address
         * and data size unset so that the start() method can be repeatedly called.
         * @param[in] usart The USART to copy to.
         * @param[in] priority The priority for this transfer.
         * @param[in] interruptFlags The DMA interrupt flags (e.g. DMA_IT_TC) that will be enabled, or 0 if none.
         */

        UsartDmaWriter(
                        const UsartPeripheral& usart,
                        uint32_t priority=DMA_Priority_High,
                        uint32_t interruptFlags=0
                    ) : UsartWriter(usart),
                            Dma(usart.getTransmitChannel(),interruptFlags) {

                DMA_PeripheralBaseAddr=reinterpret_cast<uint32_t>(&usart.getPeripheralAddress()->DR);
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
         * Start a transfer of data from source_ to the USART data register.
         *
         * @param[in] source
         *   memory address of the source data bytes.
         * @param[in] count
         *   The number of 8-bit bytes to transfer.
         */

        void send(const void *source,uint32_t count) {

            // set up the parameters for this transfer

            DMA_MemoryBaseAddr=reinterpret_cast<uint32_t>(source);
            DMA_BufferSize=count;

            // disable and then re-enable

            Dma::start();

            // finally let it go

            USART_DMACmd(_usart.getPeripheralAddress(),USART_DMAReq_Tx,ENABLE);
        }
    };
}
