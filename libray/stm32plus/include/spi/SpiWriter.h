/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include <cstdlib>
#include "spi/SpiIo.h"


namespace stm32plus {

    /**
     * @brief Base class for spi writers
     */

    class SpiWriter : public SpiIo {
        protected:
            bool _duplex;

        protected:
            SpiWriter(SpiPeripheral& peripheral);

            /**
             * Check for TXE
             */

            bool readyToSend() {
                return !!SPI_I2S_GetFlagStatus(_peripheral,SPI_I2S_FLAG_TXE);
            }

        public:

            /**
             * Virtual destructor, does nothing
             */

            virtual ~SpiWriter() {}

            /**
             * write bytes to the peripheral and optionally receive data at the same
             * time if this peripheral is operating in duplex mode.
             * @param[in] dataToSend The bytes to transmit.
             * @param[in] dataReceived Where to store the output bytes, or NULL if you're not interested
             *     in it or this peripheral is not running in duplex mode.
             * @param[in] numBytes the number of bytes to send (and maybe receive)
             * @return false if it fails.
             */

            virtual bool write(uint8_t *dataToSend,uint32_t numBytes,uint8_t *dataReceived=NULL)=0;
    };
}
