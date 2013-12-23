/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "fx/easing/EasingBase.h"

namespace stm32plus {
    namespace fx {

        /**
         * @brief x^5 based easing.
         * The acceleration of motion for a Quint easing
         * equation is greater than for a Quad, Cubic,
         * or Quart easing equation.
         */

        class QuinticEase : public EasingBase {

            public:
                /// starts motion from a zero velocity, and then accelerates
                /// motion as it executes.
                virtual double easeIn(double time_) const;

                /// starts motion fast, and then decelerates motion to
                /// a zero velocity as it executes
                virtual double easeOut(double time_) const;

                /// Combines the motion of the easeIn and easeOut methods to
                /// to start the motion from a zero velocity, accelerate motion,
                /// then decelerate to a zero velocity
                virtual double easeInOut(double time_) const;
        };
    }
}
