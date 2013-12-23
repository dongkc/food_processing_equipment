/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "fx/easing/QuarticEase.h"

namespace stm32plus {
    namespace fx {

        /*
         * Ease in
         */

        double QuarticEase::easeIn(double time_) const {
            time_/=_duration;
            return _change * time_ * time_ * time_ * time_;
        }

        /*
         * Ease out
         */

        double QuarticEase::easeOut(double time_) const {
            time_=time_ / _duration - 1;
            return -_change * (time_ * time_ * time_ * time_ - 1);
        }

        /*
         * Ease in and out
         */

        double QuarticEase::easeInOut(double time_) const {
            time_/=_duration / 2;

            if(time_ < 1)
                return _change / 2 * time_ * time_ * time_ * time_;

            time_-=2;
            return -_change / 2 * (time_ * time_ * time_ * time_ - 2);
        }
    }
}
