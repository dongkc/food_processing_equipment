/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "timing/TimeProvider.h"

namespace stm32plus {

    /**
     * @brief null time provider, always returns zero
     */

    class NullTimeProvider : public TimeProvider {

        /**
         * Get the current time. For this Null provider it is always zero.
         * @return zero.
         */

        virtual time_t getTime() const {
            return static_cast<time_t> (0);
        }
    };

}
