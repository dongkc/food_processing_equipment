/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "timing/Timer2.h"
#include "config/stdperiph.h"
#include "config/interrupts.h"
#include "gpio/GpioPort.h"


namespace stm32plus {

    /**
     * Constructor, initialise the base class
     */

    Timer2::Timer2() : Timer(TIM2) {

        // enable internal clock for this timer

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
        TIM_InternalClockConfig(TIM2);

        // set up our instance callback for interrupts

        _timerInstances[1]=this;

        // set the NVIC constant

        _irq=TIM2_IRQn;
    }


    /*
     * Enable/disable GPIO output for the timer channel
     */

    void Timer2::enableGpioOutput(uint16_t channel,bool enable) const {

        GpioPort pb(GPIOB);

        // enable GPIO AFIO

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

        // enable channel output on the GPIO pin (channels 3/4 only)

        pb.initialise(GPIO_Speed_50MHz,GPIO_Mode_AF_PP,
                channel==3 ? GPIO_Pin_10 : GPIO_Pin_11);

        GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,enable ? ENABLE : DISABLE);
    }
}


#if defined(USE_TIMER2_INTERRUPT)
extern "C" {

    extern void handleTimerInterrupt(TIM_TypeDef *whichOne,uint16_t index);

    void TIM2_IRQHandler(void) {
        handleTimerInterrupt(TIM2,1);
    }
}

#endif
