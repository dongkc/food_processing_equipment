/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "fsmc/Fsmc.h"
#include "fsmc/Fsmc8080LcdTiming.h"
#include "gpio/Gpio.h"
#include "display/graphic/DmaFsmcLcdMemoryCopy.h"


namespace stm32plus {
    namespace display {

        /**
         * @brief FSMC implementation for TFT LCD panels controlled by an 8080 interface.
         *
         * The 8080 LCD is assumed to be in 16 bit mode connected to the 16 data pins, RW, RD, NE.
         *
         * The RS (register select) operation is achieved by using an additional address line. e.g. A16.
         * A write to an address that keeps A16 low will active RS (usually active low). A write that sets
         * A16 high will set RS high and achieve a data write to the controller.
         */

        class Fsmc16BitAccessMode : public Fsmc,
                                                                public FSMC_NORSRAMInitTypeDef {

            protected:
                volatile uint16_t *_dataAddress;
                volatile uint16_t *_registerAddress;
                Gpio& _resetPin;

            public:
                Fsmc16BitAccessMode(uint32_t bank,const Fsmc8080LcdTiming& timing,uint16_t registerAddressLine,Gpio& registerPin,Gpio& resetPin);

                void enable(bool enable);

                void reset();

                void writeCommand(uint16_t command) const;
                void writeCommand(uint16_t command,uint16_t parameter) const;
                void writeData(uint16_t value) const;

                volatile uint16_t *getDataAddress() const;

                DmaFsmcLcdMemoryCopy *createDmaMemoryCopy(DMA_Channel_TypeDef *channel) const;
        };


        /**
         * Write a command to the register address
         * @param command The command to write
         */

        inline void Fsmc16BitAccessMode::writeCommand(uint16_t command) const {
            *_registerAddress=command;
        }


        /**
         * Write a command to the panel that takes a parameter
         * @param command The command to write
         * @param parameter The parameter to the command
         */

        inline void Fsmc16BitAccessMode::writeCommand(uint16_t command,uint16_t parameter) const {
            *_registerAddress=command;
            *_dataAddress=parameter;
        }


        /**
         * Write a data value to the panel
         * @param value The data value to write
         */

        inline void Fsmc16BitAccessMode::writeData(uint16_t value) const {
            *_dataAddress=value;
        }


        /**
         * Get the data address
         * @return The data address
         */

        inline volatile uint16_t *Fsmc16BitAccessMode::getDataAddress() const {
            return _dataAddress;
        }


        /**
         * Create DMA memory copier
         * @return The memory copier set to 16-bit transfers
         */

        inline DmaFsmcLcdMemoryCopy *Fsmc16BitAccessMode::createDmaMemoryCopy(DMA_Channel_TypeDef *channel) const {
            return new DmaFsmcLcdMemoryCopy(channel,_dataAddress,2);
        }
    }
}
