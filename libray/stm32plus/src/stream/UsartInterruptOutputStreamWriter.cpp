/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "stream/UsartInterruptOutputStreamWriter.h"

namespace stm32plus {

    /*
     * Constructor using interrupts for receiving data
     */

    UsartInterruptOutputStreamWriter::UsartInterruptOutputStreamWriter(UsartInterruptReader& reader_,OutputStream& os_) :
        _reader(reader_),
        _outputStream(os_) {

        // register as an observer to the USART

        _reader.insertObserver(*this);
    }


    /**
     * Notification callback when the receive interrupt is triggered
     */

    void UsartInterruptOutputStreamWriter::onNotify(
            Observable& sender_ __attribute__((unused)),
            ObservableEvent::E event_,
            void *context_) {

        if(event_==ObservableEvent::USART_Receive)
            _outputStream.write(((UsartInterruptReader::UsartReceiveEvent *)context_)->data);
    }
}
