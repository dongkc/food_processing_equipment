/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include <cstdlib>
#include "fsmc/Fsmc.h"
#include "config/stdperiph.h"
#include "gpio/GpioPort.h"


namespace stm32plus {

    /**
     * Constructor.
     * @param[in] bank The bank in library format e.g. FSMC_Bank1_NORSRAM1
     */

    Fsmc::Fsmc(uint32_t bank) {

        // save bank and init the peripheral

        _bank=bank;
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);
        RCC_AHBPeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

        // initialise the NE line for this bank

        initNE();

        // set the base address

        switch(_bank) {

            case FSMC_Bank1_NORSRAM1:
                _baseAddress=reinterpret_cast<void *>(0x60000000);
                break;

            case FSMC_Bank1_NORSRAM2:
                _baseAddress=reinterpret_cast<void *>(0x64000000);
                break;

            case FSMC_Bank1_NORSRAM3:
                _baseAddress=reinterpret_cast<void *>(0x68000000);
                break;

            case FSMC_Bank1_NORSRAM4:
                _baseAddress=reinterpret_cast<void *>(0x6C000000);
                break;

            case FSMC_Bank2_NAND:
                _baseAddress=reinterpret_cast<void *>(0x70000000);
                break;

            case FSMC_Bank3_NAND:
                _baseAddress=reinterpret_cast<void *>(0x80000000);
                break;

            case FSMC_Bank4_PCCARD:
                _baseAddress=reinterpret_cast<void *>(0x90000000);
                break;
        }

    }


    /**
     * Initialise the NE pin which is in a different location depending on the bank.
     */

    void Fsmc::initNE() {

        GPIO_TypeDef *whichOne;
        uint16_t pin;

        switch(_bank) {

            case FSMC_Bank1_NORSRAM1:        // NE1, NCE2
            case FSMC_Bank2_NAND:
                whichOne=GPIOD;
                pin=GPIO_Pin_7;
                break;

            case FSMC_Bank1_NORSRAM2:        // NE2, NCE3
            case FSMC_Bank3_NAND:
                whichOne=GPIOG;
                pin=GPIO_Pin_9;
                break;

            case FSMC_Bank1_NORSRAM3:        // NE3, NCE4_1
            case FSMC_Bank4_PCCARD:
                whichOne=GPIOG;
                pin=GPIO_Pin_10;
                break;

            case FSMC_Bank1_NORSRAM4:        // NE4
                whichOne=GPIOG;
                pin=GPIO_Pin_12;
                break;

            default:
                return;
        }

    // enable the port

        GpioPort gpio(whichOne);
        gpio.initialise(GPIO_Speed_50MHz,GPIO_Mode_AF_PP,pin);
    }


    /**
     * Get the base memory address of this bank.
     * @return The base memory address.
     */

    void *Fsmc::getBaseAddress() const {
        return _baseAddress;
    }
}
