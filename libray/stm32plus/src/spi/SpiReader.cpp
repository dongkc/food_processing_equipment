/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "spi/SpiReader.h"


namespace stm32plus {

    /**
     * Constructor
     * @param[in] peripheral The spi peripheral
     */

    SpiReader::SpiReader(SpiPeripheral& peripheral)
        : SpiIo(peripheral) {
    }
}
