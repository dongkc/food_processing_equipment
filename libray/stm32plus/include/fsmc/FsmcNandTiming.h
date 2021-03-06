/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "config/stdperiph.h"


namespace stm32plus {

    /**
     * @brief Timing class for NAND flash devices
     */

    class FsmcNandTiming : public FSMC_NAND_PCCARDTimingInitTypeDef {
        public:
            FsmcNandTiming(
                    uint32_t setupTime,
                    uint32_t waitSetupTime,
                    uint32_t holdSetupTime,
                    uint32_t hizSetupTime);
    };
}
