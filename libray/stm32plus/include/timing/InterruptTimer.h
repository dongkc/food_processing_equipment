/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "timing/Timer.h"


namespace stm32plus {


    /**
     * @brief Simple timer implementation that will trigger an interrupt
     *
     * The interrupt will fire at the given frequency and timer observers will be notified. The maximum frequency that
     * this can operate at is 60kHz.
     */

    class InterruptTimer {

        protected:
            Timer& _timer;
            uint16_t _compare;
            uint16_t _channel;

        public:
            InterruptTimer(Timer& timer,uint16_t channel,uint32_t frequency,uint8_t nvicPriority=15);

            /**
             * Get the channel that this interrupt timer is running on.
             * @return The channel number
             */

            uint16_t getChannel() const {
                return _channel;
            }


            /**
             * Get the current 16 bit comparison value
             * @return the compare value
             */

            uint16_t getCompare() const {
                return _compare;
            }
    };
}
