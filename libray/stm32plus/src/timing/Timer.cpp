/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#include "timing/Timer.h"


namespace stm32plus {

    Timer *Timer::_timerInstances[14];


    /*
     * Constructor
     */

    Timer::Timer(TIM_TypeDef *whichOne)
        : _whichOne(whichOne) {
    }


    /**
     * Enable or disable this timer
     * @param[in] enable true to enable, false to disable.
     */

    void Timer::enable(bool enable) const {
        TIM_Cmd(_whichOne,enable ? ENABLE : DISABLE);
    }


    /**
     * Set the next comparison value for a timer/channel. This should be called after a CCx interrupt
     * so that the next one fires at the correct time.
     *
     * @param[in] channel The channel number (1..4)
     * @param[in] compareVal The first comparison value.
     */

    void Timer::setCompare(uint16_t channel,uint16_t compareVal) const {

        switch(channel) {
            case 1:
                TIM_SetCompare1(_whichOne,compareVal);
                break;

            case 2:
                TIM_SetCompare2(_whichOne,compareVal);
                break;

            case 3:
                TIM_SetCompare3(_whichOne,compareVal);
                break;

            default:
                TIM_SetCompare4(_whichOne,compareVal);
                break;
        }
    }


    /**
     * Get the capture value for a channel
     */

    uint16_t Timer::getCapture(uint16_t channel) const {

        switch(channel) {
            case 1:
                return TIM_GetCapture1(_whichOne);

            case 2:
                return TIM_GetCapture2(_whichOne);

            case 3:
                return TIM_GetCapture3(_whichOne);

            default:
                return TIM_GetCapture4(_whichOne);
        }
    }


    /**
     * Get the timer number.
     * @return The timer number.
     */

    TIM_TypeDef *Timer::getWhichOne() const {
        return _whichOne;
    }


    /**
     * Output compare init for a channel.
     * @param[in] oci The initialisation values.
     * @param[in] channel The channel to initialise.
     */

    void Timer::ocInit(TIM_OCInitTypeDef& oci,uint16_t channel) const {

        switch(channel) {

            case 1:
                TIM_OC1Init(_whichOne,&oci);
                break;

            case 2:
                TIM_OC2Init(_whichOne,&oci);
                break;

            case 3:
                TIM_OC3Init(_whichOne,&oci);
                break;

            case 4:
                TIM_OC4Init(_whichOne,&oci);
                break;
        }
    }

    /*
     * Get the channel interrupt flag
     */

    uint16_t Timer::getChannelInterruptFlag(uint16_t channel) const {

        switch(channel) {
            case 1:
                return TIM_IT_CC1;

            case 2:
                return TIM_IT_CC2;

            case 3:
                return TIM_IT_CC3;

            default:
                return TIM_IT_CC4;
        }
    }


    /*
     * Process an interrupt
     */

    void Timer::processInterrupt(uint16_t interruptFlag) {

        switch(interruptFlag) {

            case TIM_IT_Break:
                notifyObservers(ObservableEvent::Timer_Break);
                break;

            case TIM_IT_CC1:
                notifyObservers(ObservableEvent::Timer_Compare,(void *)1);
                break;

            case TIM_IT_CC2:
                notifyObservers(ObservableEvent::Timer_Compare,(void *)2);
                break;

            case TIM_IT_CC3:
                notifyObservers(ObservableEvent::Timer_Compare,(void *)3);
                break;

            case TIM_IT_CC4:
                notifyObservers(ObservableEvent::Timer_Compare,(void *)4);
                break;

            case TIM_IT_Trigger:
                notifyObservers(ObservableEvent::Timer_Trigger);
                break;

            case TIM_IT_Update:
                notifyObservers(ObservableEvent::Timer_Update);
                break;
        }
    }
}

