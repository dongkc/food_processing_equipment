/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "observer/Observer.h"


namespace stm32plus {


    /**
     * @brief base class for entries in a timeline.
     *
     * This class holds the range (first..last) of the event and provides an optional reset() method
     * that gets called before a timeline starts.
     */

    class TimelineEntry : public Observer {

        protected:
            uint32_t _first;
            uint32_t _last;

        public:
            TimelineEntry(uint32_t first,uint32_t last);
            virtual ~TimelineEntry() {}

            /**
             * Get the first time
             * @return The first time
             */

            uint32_t getFirst() const {
                return _first;
            }

            /**
             * Get the last time
             * @return The last time
             */

            uint32_t getLast() const {
                return _last;
            }

            /**
             * Optional reset() call that will be called before the Timeline starts
             */

            virtual void reset() {}
    };
}
