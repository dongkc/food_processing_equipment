/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "button/PushButton.h"
#include "gpio/Gpio.h"


namespace stm32plus {

    /**
     * @brief A debounced pushbutton with autorepeat
     *
     * This class includes customised delay before the auto-repeat as well as
     * the delay between repeats.
     */

    class AutoRepeatPushButton : public PushButton {

        private:

            /**
             * our internal state
             */

            enum InternalState {

                /// waiting for action
                Idle,

                /// pressed, waiting to start repeating
                WaitingForInitial,

                /// repeating, waiting for next repeat
                WaitingForRepeat
            } _internalState;

            /// the time before repeating starts
            uint32_t _initialDelayMillis;

            /// the time between each repeat
            uint32_t _repeatDelayMillis;

            /// the last time something happened
            uint32_t _lastEventTime;

        public:
            AutoRepeatPushButton(const Gpio& pin_,bool pressedState_,uint32_t initialDelayMillis_,uint32_t repeatDelayMillis_);

            ButtonState getState();
    };
}
