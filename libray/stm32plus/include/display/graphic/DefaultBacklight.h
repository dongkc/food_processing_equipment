/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#include "display/graphic/Backlight.h"
#include "timing/Timer4.h"


namespace stm32plus {
    namespace display {


    /**
     * The default backlight is set up to use timer4, channel2.
     */

        class DefaultBacklight : public Backlight {

            protected:
              Timer4 *_timer;

            public:
                DefaultBacklight();
                ~DefaultBacklight();
        };
    }
}
