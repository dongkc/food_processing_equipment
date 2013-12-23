/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "timing/PwmOutput.h"


namespace stm32plus {
    namespace display {

        /**
         * The backlight class uses the PwmOutput class to generate a
         * dimmable backlight.
         */

        class Backlight : public PwmOutput {

            public:
                Backlight(const Timer& timer,uint16_t channel);

                void fadeTo(uint16_t newPercentage,int msPerStep);
        };
    }
}
