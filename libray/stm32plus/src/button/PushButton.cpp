/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "button/PushButton.h"
#include "timing/MillisecondTimer.h"


namespace stm32plus {

    /**
     * Constructor
     *
     * @param[in] pin_ The pin to use. The constructor will initialise this pin
     * @param[in] pressedState_ true if the pressed state is HIGH, false if it is LOW
     */

    PushButton::PushButton(const Gpio& pin_,bool pressedState_)
        : _pin(pin_) {

        // setup GPIO for the pin

        pin_.initialise(GPIO_Speed_50MHz,pressedState_ ? GPIO_Mode_IPD : GPIO_Mode_IPU);

        _pressedState=pressedState_;
        _internalState=Idle;
    }

    /**
     * Get the current state
     * @return The current state
     */

    PushButton::ButtonState PushButton::getState() {
        uint32_t newTime;
        uint8_t state;

        // read the pin and flip it if this switch reads high when open

        state=_pin.read();

        if(_pressedState)
            state^=true;

        // if state is low then wherever we were then
        // we are now back at not pressed

        if(!state) {
            _internalState=Idle;
            return NotPressed;
        }

        // sample the counter

        newTime=MillisecondTimer::millis();

        // act on the internal state machine

        switch(_internalState) {
            case Idle:
                _internalState=DebounceDelay;
                _lastTime=newTime;
                break;

            case DebounceDelay:
                if(newTime - _lastTime >= DEBOUNCE_DELAY_MILLIS) {
                    // been high for at least the debounce time

                    return Pressed;
                }
                break;
        }

        // nothing happened at this time

        return NotPressed;
    }
}
