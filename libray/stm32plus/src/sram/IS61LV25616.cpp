/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "sram/IS61LV25616.h"


namespace stm32plus {


    /**
     * Constructor
     * @param bank Which bank it's attached to, e.g.  FSMC_Bank1_NORSRAM1
     * @param accessTime The access timing for this device, e.g. 10ns
     */

    IS61LV25616::IS61LV25616(uint32_t bank,AccessTime accessTime)
        : GenericSram(bank,createTiming(accessTime),17) {            // A17 is the last address line
    }


    /**
     * Create the timing structure
     * @return The timing structure
     */

    FsmcSramTiming IS61LV25616::createTiming(AccessTime accessTime) {

        FsmcSramTiming timing;

        timing.FSMC_AccessMode=FSMC_AccessMode_A;
        timing.FSMC_AddressHoldTime=0;
        timing.FSMC_BusTurnAroundDuration=0;
        timing.FSMC_CLKDivision=0;
        timing.FSMC_DataLatency=0;

        if(accessTime==TEN_NS) {
            timing.FSMC_AddressSetupTime=0;
            timing.FSMC_DataSetupTime=1;
        }
        else if(accessTime==TWELVE_NS) {
            timing.FSMC_AddressSetupTime=0;
            timing.FSMC_DataSetupTime=1;
        }

        return timing;
    }


    /**
     * Get the total number of blocks on this device = 524288/512 = 1024 blocks
     * @return 524288/512 = 1024 blocks
     */

    uint32_t IS61LV25616::getTotalBlocksOnDevice() {
        return 1024;
    }
}
