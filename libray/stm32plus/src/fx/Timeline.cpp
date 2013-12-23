/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include <cstdlib>
#include "config/stdperiph.h"
#include "fx/Timeline.h"
#include "observer/ObserverLink.h"
#include "fx/TimelineEntry.h"


namespace stm32plus {

    /**
     * Constructor
     * @param[in] timerPeripheral The peripheral that will be used to synchronise the timeline.
     * @param[in] channel The channel that the timer is running on.
     * @param[in] frequency The desired frequency to run the timer at.
     *
     * The constructor will initialise an InterruptTimer class with the timer peripheral
     * but it will not start the timeline immediately.
     */

    Timeline::Timeline(Timer& timerPeripheral,uint16_t channel,uint16_t frequency)
        : InterruptTimer(timerPeripheral,channel,frequency) {

        // register for events from the timer

        _myLink=_timer.insertObserver(*this);
        _isRunning=false;
    }


    /**
     * Destructor
     */

    Timeline::~Timeline() {

        // stop the timer

        _timer.enable(false);

        // unregister for events from the timer

        _myLink->destroy();
    }


    /**
     * Start the timeline
     */

    void Timeline::start() {

        ObserverLink *link;

        _isRunning=true;

        // reset the entries in the timeline

        for(link=_first;link;link=link->getNext())
            ((TimelineEntry&)link->getObserver()).reset();

        _currentTime=0;

        // start the timer

        _timerTriggered=false;
        _timer.enable(true);
    }


    /**
     * Wait for the timeline to complete
     */

    void Timeline::waitForCompletion() {

        while(_isRunning)
            processTimer();
    }


    /**
     * Process a timer event, if one is ready. This is the function that must be called
     * frequently enough to ensure that the timeline runs smoothly.
     */

    void Timeline::processTimer() {

        ObserverLink *link;
        bool finished;

        // check if triggered

        if(!_timerTriggered)
            return;

        // reset for next time

        _timerTriggered=false;

        // walk the list

        finished=true;

        for(link=_first;link;link=link->getNext()) {

            // get the timeline entry at the position

            TimelineEntry& te=(TimelineEntry&)link->getObserver();

            // if the current time is in range, call it

            if(_currentTime>=te.getFirst() && _currentTime<=te.getLast()) {

                te.onNotify(*this,ObservableEvent::Timeline_Update,reinterpret_cast<void *>(_currentTime));
                finished=false;
            }
        }

        // update the current time

        _currentTime++;

        // if we're done, stop the timer

        if(finished) {
            _timer.enable(false);
            _isRunning=false;
        }
    }


    /**
     * Notification of an event from the interrupt timer. This will set the internal
     * flag that indicates processEvent should do process the timeline events next
     * time it's called. The timer capture position is advanced to the next position.
     * @param sender The event sender
     * @param event The event, which will be Timer_Compare.
     * @param context It will be NULL.
     */

    void Timeline::onNotify(
            Observable& sender __attribute__((unused)),
            ObservableEvent::E event,
            void *context __attribute__((unused))) {

        uint16_t capture;

        // check for correct event

        if(event!=ObservableEvent::Timer_Compare)
            return;

        // we have triggered

        _timerTriggered=true;

        // set the next capture time

        capture=_timer.getCapture(_channel);
        _timer.setCompare(_channel,capture+_compare);
    }
}
