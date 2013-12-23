/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "display/graphic/DefaultBacklight.h"


namespace stm32plus {
    namespace display {


        /**
         * Constructor, set up Timer4, Channel2 as the backlight
         */

        DefaultBacklight::DefaultBacklight()
            : Backlight(*(_timer=new Timer4),2) {
        }


        /**
         * Destructor
         */

        DefaultBacklight::~DefaultBacklight() {
            delete _timer;
        }
    }
}
