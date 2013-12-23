/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "display/graphic/Backlight.h"
#include "timing/MillisecondTimer.h"


namespace stm32plus {
    namespace display {


        /**
         * Default constructor. Initialise a timer at 1000Hz, initially off.
         */

        Backlight::Backlight(const Timer& timer,uint16_t channel)
          : PwmOutput(timer,channel,1000,0) {

            // turn on at zero duty cycle

            _timer.enable(true);
        }


        /**
         * fade up or down to the supplied percentage waiting
         * for msPerStep millis between each step
         * @param newPercentage 0..100
         * @param msPerStep Milliseconds to pause between each step
         */

        void Backlight::fadeTo(uint16_t newPercentage,int msPerStep) {

            int8_t direction;

            if(newPercentage==_dutyCycle)
                return;

            direction=newPercentage>_dutyCycle ? 1 : -1;

            while(newPercentage!=_dutyCycle) {
                setDutyCycle(_dutyCycle+direction);
                MillisecondTimer::delay(msPerStep);
            }
        }
    }
}
