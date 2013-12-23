/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "config/stdperiph.h"
#include "fx/TimelineEntry.h"


namespace stm32plus {

    /**
     * Constructor
     * @param[in] first The first time I want to be called
     * @param[in] last The last time I want to be called
     */

    TimelineEntry::TimelineEntry(uint32_t first,uint32_t last) {
        _first=first;
        _last=last;
    }

}
