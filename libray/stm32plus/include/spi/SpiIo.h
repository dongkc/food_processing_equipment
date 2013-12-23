/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "spi/SpiPeripheral.h"


namespace stm32plus {

    /**
     * @brief base class for SPI readers and writers
     */

    class SpiIo {

        protected:
            SpiPeripheral& _peripheral;

        protected:
            SpiIo(SpiPeripheral& peripheral) : _peripheral(peripheral) {
            }

        public:
            virtual ~SpiIo() {}

            /**
             * Get the peripheral
             * @return The peripheral class
             */

            SpiPeripheral& getPeripheral() const {
                return _peripheral;
            }
    };
}
