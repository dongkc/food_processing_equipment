/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once


#include "timing/Timer.h"


namespace stm32plus {

    /**
     * @brief Implementation of Timer for TIM4
     */

    class Timer4 : public Timer {

        public:
            Timer4();

            // overrides from Timer

            virtual void enableGpioOutput(uint16_t channel,bool enable) const;

            virtual uint16_t getTimerIndex() const {
                return 3;
            }
    };
}
