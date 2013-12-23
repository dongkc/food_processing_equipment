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
         * @brief x^3 based easing.
         * The acceleration of motion for a Cubic easing
         * equation is greater than for a Quad easing equation.
         */

        class CubicEase : public EasingBase {

            public:
                /// Starts the motion by backtracking, then reversing
                /// direction and moving toward the target
                virtual double easeIn(double time_) const;

                /// Starts the motion by moving towards the target, overshooting
                /// it slightly, and then reversing direction back toward the target
                virtual double easeOut(double time_) const;

                /// Combines the motion of the easeIn and easeOut methods to
                /// start the motion by backtracking, then reversing direction
                /// and moving toward target, overshooting target slightly,
                /// reversing direction again, and then moving back toward the target
                virtual double easeInOut(double time_) const;
        };
    }
}
