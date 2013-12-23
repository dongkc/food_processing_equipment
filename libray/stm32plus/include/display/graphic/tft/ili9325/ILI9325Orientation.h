/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once


namespace stm32plus {
    namespace display {


        /**
         * Empty generic class definition for ILI9325 orientation-dependent operations
         * Everything is provided in the specialisations.
         */

        template<Orientation TOrientation,class TAccessMode>
        class ILI9325Orientation {
        };
    }
}


/*
 * Now include the specialisations
 */

#include "display/graphic/tft/ili9325/ILI9325PortraitSpecialisation.h"
#include "display/graphic/tft/ili9325/ILI9325LandscapeSpecialisation.h"