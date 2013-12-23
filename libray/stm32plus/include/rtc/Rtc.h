/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "config/stdperiph.h"
#include "observer/Observable.h"
#include <cstdlib>
#include <stdint.h>


namespace stm32plus {

/**
 * @brief Real time clock abstraction.
 *
 * The clock source is assumed to be the LSE 32.768kHz clock.
 * The ticker is not output on the tamper pin. The user must never declare more than one instance of this
 * class to be in scope at any one time due to the use of a callback instance pointer for the interrupt handler.
 */

    class Rtc : public Observable {

        protected:
            void setupPeripheral(bool enableOverflowInterrupt_);

        public:
            /// There can be only one instance of the RTC, this refers to it and
            /// will be used by the interrupt handler to get back into the class
            static Rtc *_rtcInstance;

            Rtc(bool enableOverflowInterrupt_=false);
            ~Rtc();

            void setTick(uint32_t tick_);
            void setAlarm(uint32_t alarm_);

            uint32_t getTick() const;
    };
}
