/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "spi/SpiPeripheral.h"
#include "config/stdperiph.h"
#include "gpio/GpioPort.h"


namespace stm32plus {

    /**
     * @brief SPI1 implementation
     */

    class Spi1 : public SpiPeripheral {
        protected:
            GpioPort _pa;

        public:
            /// NSS pin
            static const uint16_t GPIO_Pin_NSS=GPIO_Pin_4;

            /// SCK pin
            static const uint16_t GPIO_Pin_SCK=GPIO_Pin_5;

            /// MISO pin
            static const uint16_t GPIO_Pin_MISO=GPIO_Pin_6;

            /// MOSI pin
            static const uint16_t GPIO_Pin_MOSI=GPIO_Pin_7;

            /*
             * constructor
             */

            Spi1(
                    uint16_t direction=SPI_Direction_2Lines_FullDuplex,
                    uint16_t mode=SPI_Mode_Master,
                    uint16_t baudRatePrescaler=SPI_BaudRatePrescaler_16,
                    uint16_t firstBit=SPI_FirstBit_MSB,
                    uint16_t cpol=SPI_CPOL_High,
                    uint16_t cpha=SPI_CPHA_2Edge,
                    uint16_t polynomial=7);


            /**
             * Set the NSS state
             * @param[in] value The log level to set
             */

            virtual void setNss(bool value) {
                if(value)
                    _pa.set(GPIO_Pin_NSS);
                else
                    _pa.reset(GPIO_Pin_NSS);
            }
    };
}
