/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "config/stdperiph.h"
#include "fsmc/Fsmc.h"
#include "fsmc/FsmcSramTiming.h"

namespace stm32plus {

    /**
     * @brief FSMC implementation for SRAM memory.
   *
   * The memory is assumed to be connected in the manner documented by ST in AN2784. The STM32
   * package is assumed to be 144 pin and the memory transfers are 16-bit.
     */

    class FsmcSram : public Fsmc,
                                     public FSMC_NORSRAMInitTypeDef {

        public:
            FsmcSram(uint32_t bank,const FsmcSramTiming& timing,const uint32_t lastAddressLineIndex);
            virtual ~FsmcSram();
    };
}
