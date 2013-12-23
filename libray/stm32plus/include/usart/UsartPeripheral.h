/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "config/stdperiph.h"


namespace stm32plus {

    /**
     * @brief Base class for USART peripheral definitions.
     *
     * Encapsulates the differing addresses and DMA channels that a peripheral has
     */

    class UsartPeripheral : public USART_InitTypeDef {

        protected:
            USART_TypeDef *_peripheralAddress;
            DMA_Channel_TypeDef *_transmitChannel;
            DMA_Channel_TypeDef *_receiveChannel;
            uint8_t _peripheralIndex;
            uint8_t _irq;

        protected:

            /*
             * Initialise the peripheral
             */

            void initialisePeripheral(
                    uint32_t baudRate_,
                    uint16_t wordLength_,
                    uint16_t parity_,
                    uint16_t stopBits_,
                    uint16_t flowControl_,
                    uint16_t mode_) {

                USART_StructInit(this);

                USART_BaudRate=baudRate_;
                USART_WordLength=wordLength_;
                USART_Parity=parity_;
                USART_StopBits=stopBits_;
                USART_HardwareFlowControl=flowControl_;
                USART_Mode=mode_;

                USART_Init(_peripheralAddress,static_cast<USART_InitTypeDef *> (this));
                USART_Cmd(_peripheralAddress,ENABLE);
            }

            /**
             * Constructor
             * @param[in] address_ The peripheral address, e.g. USART1
             * @param[in] transmitChannel_ The DMA channel for transmitting data, or NULL if there is none.
             * @param[in] receiveChannel_ The DMA channel for receiving data, or NULL if there is none.
             * @param[in] peripheralIndex_ The index (0..4) of the USART peripheral.
             * @param[in] irq_ The NVIC IRQ for this peripheral, e.g. USART1_IRQn
             */

            UsartPeripheral(
                    USART_TypeDef *address_,
                    DMA_Channel_TypeDef *transmitChannel_,
                    DMA_Channel_TypeDef *receiveChannel_,
                    uint8_t peripheralIndex_,
                    uint8_t irq_) {

                _peripheralAddress=address_;
                _transmitChannel=transmitChannel_;
                _receiveChannel=receiveChannel_;
                _peripheralIndex=peripheralIndex_;
                _irq=irq_;
            }

        public:

            /**
             * Virtual destructor, disable and de-init the peripheral
             */

      virtual ~UsartPeripheral() {
                USART_Cmd(_peripheralAddress,DISABLE);
                USART_DeInit(_peripheralAddress);
            }


      /**
       * Get the peripheral address
       * @return The address, e.g. USART1
       */

            USART_TypeDef *getPeripheralAddress() const {
                return _peripheralAddress;
            }


            /**
             * Get the DMA transmit channel.
             * @return The DMA transmit channel.
             */

            DMA_Channel_TypeDef *getTransmitChannel() const {
                return _transmitChannel;
            }


            /**
             * Get the DMA receive channel.
             * @return The DMA receive channel.
             */

            DMA_Channel_TypeDef *getReceiveChannel() const {
                return _receiveChannel;
            }


            /**
             * Cast this class to the USART peripheral address.
             * @return The USART peripheral address.
             */

            operator USART_TypeDef *() const {
                return _peripheralAddress;
            }


            /**
             * Get the peripheral index, 0..4
             * @return The peripheral index.
             */

            uint8_t getPeripheralIndex() const {
                return _peripheralIndex;
            }


            /**
             * Get the NVIC IRQ constant.
             * @return The NVIC constant, e.g. USART2_IRQn
             */

            uint8_t getIrq() const {
                return _irq;
            }
    };
}
