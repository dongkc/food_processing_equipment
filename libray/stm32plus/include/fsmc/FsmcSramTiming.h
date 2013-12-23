/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "config/stdperiph.h"
#include "fsmc/FsmcAddressDataSetupTiming.h"

namespace stm32plus {

    /**
     * Sram timing just needs address and data setup
     */

    typedef FsmcAddressDataSetupTiming FsmcSramTiming;
}
