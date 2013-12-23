/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "config/stdperiph.h"
#include "observer/Observable.h"


namespace stm32plus {

    /**
     * @brief Base class for timer implementations.
     *
     * The timer is observable for interrupts when the implementation has enabled them
     */

    class Timer : public Observable {

        protected:
            TIM_TypeDef *_whichOne;
            uint8_t _irq;

        protected:
            Timer(TIM_TypeDef *whichOne);
            virtual ~Timer() {}

        public:
            static Timer *_timerInstances[14];

        public:
            void enable(bool enable) const;
            void ocInit(TIM_OCInitTypeDef& oci,uint16_t channel) const;
            void setCompare(uint16_t channel,uint16_t compareVal) const;
            uint16_t getCapture(uint16_t channel) const;
            TIM_TypeDef *getWhichOne() const;

            /**
             * Return the NVIC IRQ constant
             * @return the constant for this timer
             */

            uint8_t getIrq() const {
                return _irq;
            }

            /**
             * Internal function that gets called back when an interrupt fires. The implementation
             * will convert the flag to an observable event and call the observers
             * @param[in] interruptFlag The flag to process.
             */

            void processInterrupt(uint16_t interruptFlag);

            /**
             * Get the channel interrupt flag (TIM_IT_CC1, ...)
             * @param[in] channel The channel number (1..4)
             * @return the appropriate interrupt flag
             */

            uint16_t getChannelInterruptFlag(uint16_t channel) const;

            /**
             * Enable the channel output on the GPIO pin.
             * @param[in] enable true to enable output, false to disable.
             * @param[in] channel The channel number (1..4).
             */

            virtual void enableGpioOutput(uint16_t channel,bool enable) const=0;


            /**
             * Get the timer index number (0..14)
             * @return the index number
             */

            virtual uint16_t getTimerIndex() const=0;
    };
}
