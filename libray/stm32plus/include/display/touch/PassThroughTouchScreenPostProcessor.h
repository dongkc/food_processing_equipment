/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once


#include "display/touch/TouchScreenPostProcessor.h"


namespace stm32plus {
    namespace display {

        /**
         * Touch screen postprocessor that passes values through without doing anything
         */

        class PassThroughTouchScreenPostProcessor : public TouchScreenPostProcessor {
            public:
                virtual ~PassThroughTouchScreenPostProcessor() {}

                /**
                 * Pass through post processor, does nothing and always returns Completed.
                 * @return Completed.
                 */

                virtual PostProcessAction postProcess(
                        Point& point __attribute__((unused)),
                        int sequenceNumber __attribute__((unused))) {
                    return Completed;
                }
        };
    }
}
