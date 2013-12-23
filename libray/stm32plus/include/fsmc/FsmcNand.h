/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "config/stdperiph.h"
#include "fsmc/Fsmc.h"
#include "fsmc/FsmcNandTiming.h"


namespace stm32plus {

    /**
     * @brief FSMC implementation for NAND flash memory
     */

    class FsmcNand : public Fsmc,
                                     public FSMC_NANDInitTypeDef {

        public:

            FsmcNand(uint32_t bank,const FsmcNandTiming& timing);
            virtual ~FsmcNand();
    };
}
