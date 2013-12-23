/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "timing/MicrosecondDelay.h"
#include "config/stdperiph.h"

namespace stm32plus {
    /*
     * Setup TIM5 to tick at 1Mhz
     */

    void MicrosecondDelay::initialise() {

        TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);

        TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
        TIM_TimeBaseStructure.TIM_Prescaler=(SystemCoreClock/1000000)-1;
        TIM_TimeBaseStructure.TIM_Period=65535;
        //TIM_TimeBaseStructure.TIM_Period=UINT16_MAX;
        TIM_TimeBaseStructure.TIM_ClockDivision=0;
        TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);

        TIM_Cmd(TIM5,ENABLE);
    }

    /*
     * Delay for the given microseconds
     */

    void MicrosecondDelay::delay(uint16_t us_) {

        TIM5->CNT=0;
        while(TIM5->CNT<=us_)
            ;
    }
}
