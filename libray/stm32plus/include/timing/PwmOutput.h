/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "timing/Timer.h"


namespace stm32plus {

    /**
     * @brief Generate a PWM signal with a customisable frequency and duty cycle.
     *
     * The PWM signal is output on the GPIO pin associated with the timer and channel.
     */

    class PwmOutput {

        protected:
            const Timer& _timer;
            uint16_t _period;
            uint16_t _channel;
            uint16_t _dutyCycle;

        public:
            PwmOutput(
                    const Timer& timer,
                    uint16_t channel,
                    uint32_t frequency,
                    uint16_t dutyCycle);

            void setDutyCycle(uint16_t dutyCycle);
    };
}
