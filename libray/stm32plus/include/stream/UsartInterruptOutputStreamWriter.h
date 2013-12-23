/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "usart/UsartInterruptReader.h"
#include "stream/OutputStream.h"
#include "observer/Observer.h"


namespace stm32plus {

    /**
     * @brief Implementation of a USART observer that listens for data and writes it to an output stream.
     *
     * This utility class provides a bridge between incoming data from a USART and an output stream that can
     * receive it. Data is read asynchronously and passed to the output stream.
     *
     * The writer is called under the interrupt handler so it is critical that the writer does not call anything
     * that depends on interrupts being enabled, such as MilisecondTimer::delay (which depends on SysTick firing)
     */

    class UsartInterruptOutputStreamWriter : public Observer {

        protected:
            UsartInterruptReader& _reader;
            OutputStream& _outputStream;

        public:

            /**
             * Constructor in interrupt mode.
             * @param[in] reader The USART that will be used.
             * @param[in] os The sink for the data when an interrupt is triggered.
             */

            UsartInterruptOutputStreamWriter(UsartInterruptReader& reader,OutputStream& os);
            virtual ~UsartInterruptOutputStreamWriter() {}

            // overrides from observer

            virtual void onNotify(Observable& sender_,ObservableEvent::E event_,void *context_);
    };
}

