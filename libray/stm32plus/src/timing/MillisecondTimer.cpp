/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "timing/MillisecondTimer.h"
#include "misc.h"
#include "config/stdperiph.h"


extern "C" {
    volatile uint32_t _counter;
}


namespace stm32plus {

    /**
     * Delay for given time. Waits for the current value of the systick counter to reach a target.
     * @param millis_ The amount of time to wait.
     */

    void MillisecondTimer::delay(uint32_t millis_) {
        uint32_t target;

        target=_counter + millis_;
        while(_counter < target)
            ;
    }

    /**
     * Get the current value of the systick counter.
     * @return The current value of the counter.
     */

    uint32_t MillisecondTimer::millis() {
        return _counter;
    }

    /**
     * Initialise SysTick to tick at 1ms by initialising it with SystemCoreClock/1000.
     */

    void MillisecondTimer::initialise() {
        _counter=0;
        SysTick_Config(SystemCoreClock / 40000);
    }
}

/**
 * SysTick interrupt handler
 */

//extern "C" {
//    void SysTick_Handler(void) {
//        _counter++;
//    }
//}
