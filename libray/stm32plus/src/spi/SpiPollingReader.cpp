/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "spi/SpiPollingReader.h"


namespace stm32plus {

    /**
     * Constructor
     * @param[in] peripheral The SPI peripheral to read from
     */

    SpiPollingReader::SpiPollingReader(SpiPeripheral& peripheral)
        : SpiReader(peripheral) {
    }


    /**
     * Read a word from the peripheral
     */

    bool SpiPollingReader::read(uint8_t& byte) {

        while(!readyToReceive())
            if(_peripheral.hasError())
                return false;

        byte=SPI_I2S_ReceiveData(_peripheral);
        return true;
    }
}
