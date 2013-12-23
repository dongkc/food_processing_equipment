/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "usart/UsartInterruptWriter.h"
#include "stream/InputStream.h"
#include "observer/Observer.h"

namespace stm32plus {

    /**
     * @brief Implementation of a USART TX observer that reads data from the input stream and sends it to the USART
     *
     * This utility class provides a bridge between an input stream and a USART peripheral. Ensure some data is available
     * in the stream then call enableInterrupt() on the writer. The data will be drained asynchronously from the stream
     * and sent to the USART. When the stream is empty interrupts are disabled ready for you to send the next batch.
     */

    class UsartInterruptInputStreamReader : public Observer {

        protected:
            UsartInterruptWriter& _writer;
            InputStream& _inputStream;

        public:
            UsartInterruptInputStreamReader(UsartInterruptWriter& writer_,InputStream& is_);

            /**
             * Virtual destructor does nothing
             */

            virtual ~UsartInterruptInputStreamReader() {
            }

            // overrides from observer

            virtual void onNotify(Observable& sender_,ObservableEvent::E event_,void *context_);
    };
}

