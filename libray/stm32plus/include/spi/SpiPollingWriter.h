/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "SpiWriter.h"


namespace stm32plus {

    /**
     * @brief Polling SPI writer.
     *
     * Write operations block
     */

    class SpiPollingWriter : public SpiWriter {

        public:
            SpiPollingWriter(SpiPeripheral& peripheral);
            virtual ~SpiPollingWriter() {}

            virtual bool write(uint8_t *dataToSend,uint32_t numBytes,uint8_t *dataReceived=NULL);
    };
}
