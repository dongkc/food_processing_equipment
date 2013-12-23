/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "spi/SpiPeripheral.h"
#include "config/stdperiph.h"

namespace stm32plus {

    /**
     * @brief SPI3 implementation
     */

    class Spi3 : public SpiPeripheral {

        public:

            /// SCK pin
            static const uint16_t GPIO_Pin_SCK=GPIO_Pin_3;

            /// MISO pin
            static const uint16_t GPIO_Pin_MISO=GPIO_Pin_4;

            /// MOSI pin
            static const uint16_t GPIO_Pin_MOSI=GPIO_Pin_5;

            /*
             * constructor
             */

            Spi3(
                    uint16_t direction=SPI_Direction_2Lines_FullDuplex,
                    uint16_t mode=SPI_Mode_Master,
                    uint16_t baudRatePrescaler=SPI_BaudRatePrescaler_2,
                    uint16_t firstBit=SPI_FirstBit_MSB,
                    uint16_t cpol=SPI_CPOL_High,
                    uint16_t cpha=SPI_CPHA_2Edge,
                    uint16_t polynomial=7);

        /**
         * Set the NSS state - there is no NSS for SPI3
         */

        virtual void setNss(bool value __attribute__((unused))) {
        }
    };
}
