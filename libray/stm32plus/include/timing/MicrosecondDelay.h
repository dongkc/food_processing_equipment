/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include <stdint.h>

namespace stm32plus {

    /**
     * @brief Delay for a number of microseconds
     */

    class MicrosecondDelay {
        public:

            /**
             * Initialise the timer.
             */

            static void initialise();


            /**
             * Delay synchronously to the caller for the given number of microseconds.
             * @param[in] us_ The number of microseconds to delay for.
             */

            static void delay(uint16_t us_);
    };
}
