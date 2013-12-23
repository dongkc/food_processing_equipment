/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "spi/SpiWriter.h"


namespace stm32plus {

    /**
     * Constructor
     * @param[in] peripheral_ The spi peripheral
     */

    SpiWriter::SpiWriter(SpiPeripheral& peripheral)
        : SpiIo(peripheral) {

        _duplex=_peripheral.SPI_Direction==SPI_Direction_2Lines_FullDuplex;
    }
}
