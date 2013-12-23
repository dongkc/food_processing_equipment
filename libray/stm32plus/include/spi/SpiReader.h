/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "spi/SpiIo.h"


namespace stm32plus {

    /**
     * @brief Base class for spi readers
     */

    class SpiReader : public SpiIo {
        protected:
            SpiReader(SpiPeripheral& peripheral);

            /**
             * Check for RXNE
             */

            bool readyToReceive() {
                return !!SPI_I2S_GetFlagStatus(_peripheral,SPI_I2S_FLAG_RXNE);
            }

        public:

            /**
             * Virtual destructor, does nothing
             */

            virtual ~SpiReader() {}


            /**
             * Read bytes from the peripheral.
             * @param[out] buffer Where to read data to.
             * @param[in] numBytes The number of bytes to read
             * @return false if it fails.
             */

            virtual bool read(uint8_t *buffer,uint32_t numBytes)=0;
    };
}
