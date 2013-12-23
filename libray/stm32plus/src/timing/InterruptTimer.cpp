/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "timing/InterruptTimer.h"
#include "config/stdperiph.h"
#include "nvic/Nvic.h"


namespace stm32plus {


    /**
     * Constructor
     * @param[in] timer The timer peripheral to use.
     * @param[in] channel The channel number (1..4)
     * @param[in] frequency The frequency of the interrupt in Hz
     * @param[in] nvicPriority The relative priority of the interrupt. The default is very low (15) so that this
     *     handler may use other peripherals that require interrupts to work.
     */

    InterruptTimer::InterruptTimer(Timer& timer,uint16_t channel,uint32_t frequency,uint8_t nvicPriority)
     : _timer(timer) {

        TIM_OCInitTypeDef oci;
        TIM_TimeBaseInitTypeDef tbi;
        uint16_t prescaler;

        _channel=channel;

        // base initialisation for the timer at 60khz

        prescaler=static_cast<uint16_t>(SystemCoreClock/60000L)-1;

        // base timer initialisation

        TIM_TimeBaseStructInit(&tbi);

        tbi.TIM_Period=65535;
        tbi.TIM_Prescaler=prescaler;
        tbi.TIM_ClockDivision=0;
        tbi.TIM_CounterMode=TIM_CounterMode_Up;

        TIM_TimeBaseInit(timer.getWhichOne(),&tbi);

        // calculate the compare value as 60khz / desired frequency

        _compare=static_cast<uint16_t>(60000L/frequency);

   // timing mode configuration

        TIM_OCStructInit(&oci);

        oci.TIM_OCMode=TIM_OCMode_Timing;
        oci.TIM_OutputState=TIM_OutputState_Enable;
        oci.TIM_Pulse=_compare;
        oci.TIM_OCPolarity=TIM_OCPolarity_High;

        _timer.ocInit(oci,channel);

        // enable interrupts

        Nvic::configureIrq(timer.getIrq(),ENABLE,nvicPriority);
        TIM_ITConfig(timer.getWhichOne(),timer.getChannelInterruptFlag(channel),ENABLE);
    }
}
