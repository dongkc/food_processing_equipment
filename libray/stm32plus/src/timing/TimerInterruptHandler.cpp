/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "observer/Observable.h"
#include "config/interrupts.h"
#include "config/stdperiph.h"
#include "timing/Timer.h"


using namespace stm32plus;


extern "C" {


#if defined(USE_TIMER2_INTERRUPT) || \
        defined(USE_TIMER3_INTERRUPT) || \
        defined(USE_TIMER4_INTERRUPT) || \
        defined(USE_TIMER5_INTERRUPT) || \
        defined(USE_TIMER6_INTERRUPT) || \
        defined(USE_TIMER7_INTERRUPT)

    void handleTimerInterrupt(TIM_TypeDef *whichOne,uint16_t index) {

        if(TIM_GetITStatus(whichOne,TIM_IT_CC1)!=RESET) {
            Timer::_timerInstances[index]->processInterrupt(TIM_IT_CC1);
            TIM_ClearITPendingBit(whichOne,TIM_IT_CC1);
        }

        if(TIM_GetITStatus(whichOne,TIM_IT_CC2)!=RESET) {
            Timer::_timerInstances[index]->processInterrupt(TIM_IT_CC2);
            TIM_ClearITPendingBit(whichOne,TIM_IT_CC2);
        }

        if(TIM_GetITStatus(whichOne,TIM_IT_CC3)!=RESET) {
            Timer::_timerInstances[index]->processInterrupt(TIM_IT_CC3);
            TIM_ClearITPendingBit(whichOne,TIM_IT_CC3);
        }

        if(TIM_GetITStatus(whichOne,TIM_IT_CC4)!=RESET) {
            Timer::_timerInstances[index]->processInterrupt(TIM_IT_CC4);
            TIM_ClearITPendingBit(whichOne,TIM_IT_CC4);
        }
    }

#endif
}
