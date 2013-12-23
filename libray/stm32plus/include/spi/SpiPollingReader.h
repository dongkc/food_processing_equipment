/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "spi/SpiReader.h"


namespace stm32plus {


    /**
     * @brief Polling SPI reader.
     *
     * Read operations block until data arrives.
     */

    class SpiPollingReader : public SpiReader {

        public:
            SpiPollingReader(SpiPeripheral& peripheral);
            virtual ~SpiPollingReader() {}

            virtual bool read(uint8_t& byte);
    };
}
