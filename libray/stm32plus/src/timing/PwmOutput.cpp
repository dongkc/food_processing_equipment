/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "timing/PwmOutput.h"


namespace stm32plus {


    /**
     * Constructor. Set up the class with the given defaults.
     *
     * @param[in] timer A reference to the timer used for this. Must remain in scope
     * @param[in] channel The channel to use.
     * @param[in] frequency Frequency in hertz.
     * @param[in] dutyCycle Duty cycle as a percentage.
     */

    PwmOutput::PwmOutput(const Timer& timer,uint16_t channel,uint32_t frequency,uint16_t dutyCycle)
        : _timer(timer) {

        TIM_TimeBaseInitTypeDef tbi;
        uint16_t prescaler;

        // remember channel number

        _channel=channel;

        // enable this channel for output on the GPIO pin

        _timer.enableGpioOutput(channel,false);

        // set the clock to 24Mhz (the lowest standard frequency for an STM32 core clock)

        prescaler=static_cast<uint16_t>(SystemCoreClock/24000000L);
        _period=static_cast<uint16_t>(24000000L/frequency);

    // base timer initialisation

        TIM_TimeBaseStructInit(&tbi);

        tbi.TIM_Period=_period-1;
        tbi.TIM_Prescaler=prescaler-1;
        tbi.TIM_ClockDivision=0;
        tbi.TIM_CounterMode=TIM_CounterMode_Up;

        TIM_TimeBaseInit(timer.getWhichOne(),&tbi);

    // set the duty cycle

        setDutyCycle(dutyCycle);
    }


    /**
     * Set the duty cycle to the given percentage.
     * @param[in] dutyCycle The percentage duty cycle (0..100)
     */

    void PwmOutput::setDutyCycle(uint16_t dutyCycle) {

        TIM_OCInitTypeDef oci;
        uint16_t pulse;

        // remember value

        _dutyCycle=dutyCycle;

        pulse=static_cast<uint16_t>(((uint32_t)_period*(uint32_t)dutyCycle)/100L);

   // PWM1 Mode configuration

        TIM_OCStructInit(&oci);

        oci.TIM_OCMode=TIM_OCMode_PWM1;
        oci.TIM_OutputState=TIM_OutputState_Enable;
        oci.TIM_Pulse=pulse;
        oci.TIM_OCPolarity=TIM_OCPolarity_High;

        _timer.ocInit(oci,_channel);
    }
}
