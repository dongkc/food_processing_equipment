/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "fx/easing/LinearEase.h"

namespace stm32plus {
    namespace fx {

        /*
         * Ease in
         */

        double LinearEase::easeIn(double time_) const {
            return _change * time_ / _duration;
        }

        /*
         * Ease out
         */

        double LinearEase::easeOut(double time_) const {
            return easeIn(time_);
        }

        /*
         * Ease in and out
         */

        double LinearEase::easeInOut(double time_) const {
            return easeIn(time_);
        }
    }
}
