/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include <stdint.h>

/**
 * The stm32plus namespace is the top-level namespace for all classes in the library.
 */

namespace stm32plus {

    /**
     * @brief Millisecond delay counter on TIM2
     */

    class MillisecondTimer {

        public:
            static void initialise();
            static void delay(uint32_t millis_);
            static uint32_t millis();
    };
}

