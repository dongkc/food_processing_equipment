/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "rtc/Rtc.h"
#include "nvic/Nvic.h"
#include "config/stdperiph.h"
#include "config/interrupts.h"

namespace stm32plus {

    /// Pointer to the only instance of this class
    Rtc *Rtc::_rtcInstance=NULL;

    /**
     * Constructor.
     * @param[in] enableOverflowInterrupt_ true if we are enabling the overflow interrupt.
     */

    Rtc::Rtc(bool enableOverflowInterrupt_) {

        Nvic::configureIrq(RTC_IRQn);

        // remember this instance and configure the peripheral

        _rtcInstance=this;
        setupPeripheral(enableOverflowInterrupt_);
    }

    /*
     * Set up the RTC.
     */

    void Rtc::setupPeripheral(bool enableOverflowInterrupt_) {

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);

        PWR_BackupAccessCmd(ENABLE); // allow backup domain access
        BKP_DeInit(); // reset backup domain

        RCC_LSEConfig(RCC_LSE_ON);

        while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)==RESET) {
        } // Wait till LSE is ready

        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); // Select the RTC Clock Source
        RCC_RTCCLKCmd(ENABLE); // Enable RTC Clock

        RTC_WaitForSynchro(); // Wait for RTC registers synchronization
        RTC_WaitForLastTask(); // Wait until last write operation on RTC registers has finished

        RTC_ITConfig(RTC_IT_SEC,ENABLE); // Enable the RTC Second
        RTC_WaitForLastTask(); // Wait until last write operation on RTC registers has finished
        RTC_SetPrescaler(32767); // Set RTC prescaler: set RTC period to 1sec
        RTC_WaitForLastTask(); // Wait until last write operation on RTC registers has finished

        // enable overflow interrupt if user wants it

        if(enableOverflowInterrupt_)
            RTC_ITConfig(RTC_IT_OW,ENABLE);
    }


    /**
     * Get the current tick.
     * @return The current tick.
     */

    uint32_t Rtc::getTick() const {
        RTC_WaitForLastTask();
        return ::RTC_GetCounter();
    }

    /**
     * Set the alarm.
     * @param[in] alarm_ The alarm value.
     */

    void Rtc::setAlarm(uint32_t alarm_) {
        RTC_WaitForLastTask();
        RTC_ITConfig(RTC_IT_ALR,ENABLE);
        RTC_SetAlarm(alarm_);
        RTC_WaitForLastTask();
    }

    /**
     * Set the tick.
     * @param[in] tick_ The new tick value.
     */

    void Rtc::setTick(uint32_t tick_) {
        RTC_WaitForLastTask();
        RTC_SetCounter(tick_);
        RTC_WaitForLastTask();
    }

    /**
     * Destructor, disable all interrupts.
     */

    Rtc::~Rtc() {

        // disable interrupts

        RTC_WaitForLastTask();
        RTC_ITConfig(RTC_IT_ALR,DISABLE);
        RTC_ITConfig(RTC_IT_SEC,DISABLE);
        RTC_ITConfig(RTC_IT_OW,DISABLE);
    }
}

#if defined(USE_RTC_INTERRUPT)

using namespace stm32plus;

extern "C" {

    void RTC_IRQHandler(void) {

        // check the ticker

        if(RTC_GetITStatus(RTC_IT_SEC)!=RESET) {
            Rtc::_rtcInstance->notifyObservers(ObservableEvent::RTC_Tick);
            RTC_ClearITPendingBit(RTC_FLAG_SEC);
        }

        // check the alarm

        if(RTC_GetITStatus(RTC_IT_ALR)!=RESET) {
            Rtc::_rtcInstance->notifyObservers(ObservableEvent::RTC_Alarm);
            RTC_ClearITPendingBit(RTC_FLAG_ALR);
        }

        // check the overflow

        if(::RTC_GetITStatus(RTC_IT_OW)!=RESET) {
            Rtc::_rtcInstance->notifyObservers(ObservableEvent::RTC_Overflow);
            RTC_ClearITPendingBit(RTC_FLAG_OW);
        }
    }
}

#endif
