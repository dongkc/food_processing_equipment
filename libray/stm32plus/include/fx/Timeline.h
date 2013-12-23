/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "timing/InterruptTimer.h"
#include "observer/Observer.h"
#include "observer/Observable.h"


namespace stm32plus {


    /**
     * @brief a timeline class manages the timed dispatch of calls to classes on the Timeline.
     *
     * This class is generally used to manage asynchronous animation. The class is an observer of interrupts
     * from the Timer and is observable for events on the timeline. The Observers must be instances of TimelineEntry
     */

    class Timeline : public InterruptTimer,
                     public Observer,
                                     public Observable {

        protected:
            ObserverLink *_myLink;
            uint32_t _currentTime;
            bool _isRunning;
            volatile bool _timerTriggered;

        public:
            Timeline(Timer& timerPeripheral,uint16_t channel,uint16_t frequency);
            virtual ~Timeline();

            void start();
            void processTimer();
            void waitForCompletion();

            /**
             * Return true if the timeline is currently running
             * @return true if it's running
             */

            bool isRunning() const {
                return _isRunning;
            }

            // notification that an event has occurred
            virtual void onNotify(Observable& sender,ObservableEvent::E event,void *context);
    };
}
