/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "spi/Spi2.h"
#include "nvic/Nvic.h"
#include "gpio/GpioPort.h"

namespace stm32plus {

    /**
     * Constructor. Initialise the peripheral. The parameters to this function match those for SPI_InitTypeDef.
     * The default SPI mode is 3 (CPOL=CPHA=1)
     *
     * @param[in] direction SPI direction, default is SPI_Direction_2Lines_FullDuplex
     * @param[in] mode Master or slave, default is SPI_Mode_Master
     * @param[in] baudRatePrescaler The clock divider applied to fPCLK to get the SPI speed.
     * @param[in] firstBit Bit ordering. Default is SPI_FirstBit_MSB.
     * @param[in] cpol Clock polarity. Default is SPI_CPOL_High.
     * @param[in] cpha Clock phase. Default is SPI_CPHA_2Edge.
     * @param[in] polynomial CRC polynomial, default is 7.
     */

    Spi2::Spi2(
            uint16_t direction,
            uint16_t mode,
            uint16_t baudRatePrescaler,
            uint16_t firstBit,
            uint16_t cpol,
            uint16_t cpha,
            uint16_t polynomial) : SpiPeripheral(SPI2,DMA1_Channel5,DMA1_Channel4,1,SPI2_IRQn), _pb(GPIOB) {

        // spi peripheral clock

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);

        if(mode==SPI_Mode_Master) {
            _pb.initialise(GPIO_Speed_50MHz,GPIO_Mode_AF_PP,GPIO_Pin_SCK | GPIO_Pin_MOSI);
            _pb.initialise(GPIO_Speed_50MHz,GPIO_Mode_IN_FLOATING,GPIO_Pin_MISO);
            _pb.initialise(GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIO_Pin_NSS);

        } else {
            _pb.initialise(GPIO_Speed_50MHz,GPIO_Mode_IN_FLOATING,GPIO_Pin_SCK | GPIO_Pin_MOSI | GPIO_Pin_NSS);
            _pb.initialise(GPIO_Speed_50MHz,GPIO_Mode_AF_PP,GPIO_Pin_MISO);
        }

        // initialise

        initialisePeripheral(direction,mode,baudRatePrescaler,firstBit,cpol,cpha,polynomial);
    }
}
