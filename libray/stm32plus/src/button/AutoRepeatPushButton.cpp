/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "button/AutoRepeatPushButton.h"
#include "timing/MillisecondTimer.h"


namespace stm32plus {

    /**
     * Constructor
     * @param[in] pin_ The pin that the button is wired to.
     * @param[in] pressedState_ true if the pressed state is HIGH, false if it is low.
     * @param[in] initialDelayMillis_ The delay before repeating starts.
     * @param[in] repeatDelayMillis_ The delay between repeats.
     */

    AutoRepeatPushButton::AutoRepeatPushButton(const Gpio& pin_,bool pressedState_,uint32_t initialDelayMillis_,uint32_t repeatDelayMillis_)
        : PushButton(pin_,pressedState_) {

    // setup the encapsulated class and remember params

        _initialDelayMillis=initialDelayMillis_;
        _repeatDelayMillis=repeatDelayMillis_;
    }


    /**
     * Get the current state of the button.
     * @return The current state.
     */

    PushButton::ButtonState AutoRepeatPushButton::getState() {

        uint32_t now;

    // if button is not pressed then our state machine is reset

        if(getState()==NotPressed)
        {
            _internalState=Idle;
            return NotPressed;
        }

        now=MillisecondTimer::millis();

        switch(_internalState)
        {
        // first press, record that we are now waiting for the
        // initial repeat and save the time we started.

            case Idle:
                _internalState=WaitingForInitial;
                _lastEventTime=now;
                return Pressed;

        // lead up to the initial repeat. When the time is reached
        // advance the state into the multi-repeat stage

            case WaitingForInitial:
                if(now-_lastEventTime>=_initialDelayMillis)
                {
                    _internalState=WaitingForRepeat;
                    _lastEventTime=now;
                    return Pressed;
                }
                else
                    return NotPressed;

        // we're in the repeat loop. Return 'Pressed' each time
        // the time interval is passed

            case WaitingForRepeat:
                if(now-_lastEventTime>=_repeatDelayMillis)
                {
                    _lastEventTime=now;
                    return Pressed;
                }
                else
                    return NotPressed;
        }

    // should never get here

        return NotPressed;
    }
}
