/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "timing/Timer4.h"
#include "config/stdperiph.h"
#include "config/interrupts.h"
#include "gpio/GpioPort.h"

namespace stm32plus {

    /**
     * Constructor, initialise the base class
     */

    Timer4::Timer4() : Timer(TIM4) {

        // enable internal clock for this timer

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
        TIM_InternalClockConfig(TIM4);

        // set up our instance callback for interrupts

        _timerInstances[3]=this;

        // set the NVIC constant

        _irq=TIM4_IRQn;
    }


    /*
     * Enable/disable GPIO output for the timer channel
     */

    void Timer4::enableGpioOutput(uint16_t channel,bool enable) const {

        GpioPort pd(GPIOD);

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

        // enable channel output on the GPIO pin

        pd.initialise(GPIO_Speed_50MHz,GPIO_Mode_AF_PP,
                channel==1 ? GPIO_Pin_12 :
                channel==2 ? GPIO_Pin_13 :
                channel==3 ? GPIO_Pin_14 : GPIO_Pin_15);

        GPIO_PinRemapConfig(GPIO_Remap_TIM4,enable ? ENABLE : DISABLE);
    }
}


#if defined(USE_TIMER4_INTERRUPT)
extern "C" {

    extern void handleTimerInterrupt(TIM_TypeDef *whichOne,uint16_t index);

    void TIM4_IRQHandler(void) {
        handleTimerInterrupt(TIM4,3);
    }
}
#endif
