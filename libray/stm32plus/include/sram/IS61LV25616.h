/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "sram/GenericSram.h"


namespace stm32plus {

    /**
     * @brief Implementation of the ISSI IS61LV25616 256K x 16 (4Mbit) SRAM
     */

    class IS61LV25616 : public GenericSram {

        public:

            /**
             * Access time of this device. Used for setting up the FSMC timing
             */

            enum AccessTime {
                /// 10ns
                TEN_NS,
                /// 12ns
                TWELVE_NS
            };

        protected:

            FsmcSramTiming createTiming(AccessTime accessTime);

        public:

            IS61LV25616(uint32_t bank,AccessTime accessTime);
            virtual ~IS61LV25616() {}

            // overrides from BlockDevice

            virtual uint32_t getTotalBlocksOnDevice();
    };
}
