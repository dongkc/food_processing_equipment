/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "config/stdperiph.h"
#include "error/ErrorProvider.h"


namespace stm32plus {

    /**
     * @brief SPI base class
     */

    class SpiPeripheral : public SPI_InitTypeDef {

        protected:
            SPI_TypeDef *_peripheralAddress;
            DMA_Channel_TypeDef *_transmitChannel;
            DMA_Channel_TypeDef *_receiveChannel;
            uint8_t _peripheralIndex;
            uint8_t _irq;

        public:
            enum {
                E_SPI_ERROR = 1
            };

        protected:

            /*
             * Initialise the device
             */

            void initialisePeripheral(
                    uint16_t direction,
                    uint16_t mode,
                    uint16_t baudRatePrescaler,
                    uint16_t firstBit,
                    uint16_t cpol,
                    uint16_t cpha,
                    uint16_t polynomial) {

                SPI_StructInit(this);

                SPI_Direction=direction;
                SPI_Mode=mode;
                SPI_DataSize=SPI_DataSize_8b;
                SPI_CPOL=cpol;
                SPI_CPHA=cpha;
                SPI_NSS=SPI_NSS_Soft;
                SPI_BaudRatePrescaler=baudRatePrescaler;
                SPI_FirstBit=firstBit;
                SPI_CRCPolynomial=polynomial;

            // initialise the peripheral

                SPI_Init(_peripheralAddress,this);

            // NSS is soft, ensure it's high to begin with

                setNss(true);

            // enable SPI

                SPI_Cmd(_peripheralAddress,ENABLE);
            }


            /**
             * Constructor
             * @param[in] address The peripheral address, e.g. USART1
             * @param[in] transmitChannel The DMA channel for transmitting data, or NULL if there is none.
             * @param[in] receiveChannel The DMA channel for receiving data, or NULL if there is none.
             * @param[in] peripheralIndex The index (0..4) of the USART peripheral.
             * @param[in] irq The NVIC IRQ for this peripheral, e.g. USART1_IRQn
             */

            SpiPeripheral(
                    SPI_TypeDef *address,
                    DMA_Channel_TypeDef *transmitChannel,
                    DMA_Channel_TypeDef *receiveChannel,
                    uint8_t peripheralIndex,
                    uint8_t irq) {

                _peripheralAddress=address;
                _transmitChannel=transmitChannel;
                _receiveChannel=receiveChannel;
                _peripheralIndex=peripheralIndex;
                _irq=irq;
            }

        public:

            /**
             * Destructor. Disable and de-init the peripheral
             */

            virtual ~SpiPeripheral() {
                SPI_Cmd(_peripheralAddress,DISABLE);
                SPI_I2S_DeInit(_peripheralAddress);
            }

      /**
       * Get the peripheral address
       * @return The address, e.g. SPI1
       */

            SPI_TypeDef *getPeripheralAddress() const {
                return _peripheralAddress;
            }


            /**
             * Set soft NSS to a logic level
             * @param[in] value The logic level to set
             */

            virtual void setNss(bool value)=0;


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
             * Cast this class to the SPI peripheral address.
             * @return The SPI peripheral address.
             */

            operator SPI_TypeDef *() const {
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
             * Check if the device has an error status
             */

            bool hasError() const {

                FlagStatus status;

                if((status=SPI_I2S_GetFlagStatus(_peripheralAddress,SPI_FLAG_CRCERR | SPI_FLAG_MODF | SPI_I2S_FLAG_OVR))!=0)
                    return !errorProvider.set(ErrorProvider::ERROR_PROVIDER_SPI,E_SPI_ERROR,status);

                return false;
            }


            /**
             * Get the NVIC IRQ constant.
             * @return The NVIC constant, e.g. SPI2_IRQn
             */

            uint8_t getIrq() const {
                return _irq;
            }
    };
}
