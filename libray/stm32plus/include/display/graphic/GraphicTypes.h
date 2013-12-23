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
         * External (abstract) representation of RGB pixel:
         *
         * AAAAAAAARRRRRRRRGGGGGGGGBBBBBBBB
         *  A = alpha (reserved)
         *  R = red
         *  G = green
         *  B = blue
         */

        typedef uint32_t RGBE;

        /**
         * Internal (defined by the controller code) representation of RGB pixel
         */

        typedef void *RGBI;


        /**
         * LCD orientation: portrait or landscape
         */

        namespace Orientation {
            /// LCD orientation
            enum E {
                /// landscape (long side horizontal)
                Landscape,

                // portrait (long side vertical)
                Portrait
            };
        }


        /**
         * scrolling directions
         */

        namespace ScrollDirection {

            /// Scrolling directions
            enum E {
                /// no scrolling
                None=0x0,

                /// scroll vertically
                Vertical=0x1,

                /// scrol horizontally
                Horizontal=0x2
            };
        }
    }
}
