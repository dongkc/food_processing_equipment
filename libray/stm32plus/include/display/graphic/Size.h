/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include <stdint.h>


namespace stm32plus {
    namespace display {

        /**
         * @brief A pixel size structure
         */

        struct Size {

                /// The width
                int16_t Width;

                /// The height
                int16_t Height;

                Size() {}

                /**
                 * Constructor
                 * @param[in] width The width parameter.
                 * @param[in] height The height parameter.
                 */

                Size(int16_t width,int16_t height) :
                    Width(width), Height(height) {
                }
        };
    }
}
