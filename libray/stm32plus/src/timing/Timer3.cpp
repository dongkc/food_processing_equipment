/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "timing/Timer3.h"
#include "config/stdperiph.h"
#include "config/interrupts.h"
#include "gpio/GpioPort.h"


namespace stm32plus {

    /**
     * Constructor, initialise the base class
     */

    Timer3::Timer3() : Timer(TIM3) {

    // enable internal clock for this timer

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
        TIM_InternalClockConfig(TIM3);

        // set up our instance callback for interrupts

        _timerInstances[2]=this;

        // set the NVIC constant

        _irq=TIM3_IRQn;
    }


    /*
     * Enable/disable GPIO output for the timer channel
     */

    void Timer3::enableGpioOutput(uint16_t channel,bool enable) const {

        GpioPort pa(GPIOA);
        GpioPort pb(GPIOB);

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

        // enable channel output on the GPIO pin

        switch (channel) {
            case 1:
                pa.initialise(GPIO_Speed_50MHz,GPIO_Mode_AF_PP,GPIO_Pin_6);
                break;
            case 2:
                pa.initialise(GPIO_Speed_50MHz,GPIO_Mode_AF_PP,GPIO_Pin_7);
                break;
            case 3:
                pb.initialise(GPIO_Speed_50MHz,GPIO_Mode_AF_PP,GPIO_Pin_0);
                break;
            default:
                pb.initialise(GPIO_Speed_50MHz,GPIO_Mode_AF_PP,GPIO_Pin_1);
        }

        GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,enable ? ENABLE : DISABLE);
    }
}

#if defined(USE_TIMER3_INTERRUPT)
extern "C" {

    extern void handleTimerInterrupt(TIM_TypeDef *whichOne,uint16_t index);

    void TIM3_IRQHandler(void) {
        handleTimerInterrupt(TIM3,2);
    }
}
#endif
