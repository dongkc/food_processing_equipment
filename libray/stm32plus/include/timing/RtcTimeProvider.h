/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "timing/TimeProvider.h"
#include "rtc/Rtc.h"


namespace stm32plus {

    /**
     * @brief Time provider that uses the real time clock
     */

    class RtcTimeProvider : public TimeProvider {
        protected:
            const Rtc& _rtc;

        public:

            /**
             * Constructor.
             * @param[in] rtc_ The RTC. Caller supplied parameter, must not go out of scope.
             */

            RtcTimeProvider(const Rtc& rtc_) :
                _rtc(rtc_) {
            }


            /**
             * Return the time. Actually returns the tick-count from the RTC.
             * @return The tick count.
             */

            virtual time_t getTime() const {
                return _rtc.getTick();
            }
    };

}
