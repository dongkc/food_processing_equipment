/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "stream/UsartInterruptInputStreamReader.h"


namespace stm32plus {


    /**
     * Constructor. Registers this class as an observer to the interrupt writer.
     * @param[in] writer_ The interrupt-based USART writer.
     * @param[in] is_ The source of data for the transmission.
     */

    UsartInterruptInputStreamReader::UsartInterruptInputStreamReader(UsartInterruptWriter& writer_,InputStream& is_)
        : _writer(writer_),
          _inputStream(is_) {

        // register as an observer to the USART

        _writer.insertObserver(*this);
    }


    /**
     * Notification that a transmit can happen.
     * @param[in] sender_ The source of the event (will be the USART peripheral).
     * @param[in] event_ The event type. We care about USART_ReadyToTransmit.
     * @param[in] context_ Will be NULL for our event.
     */

    void UsartInterruptInputStreamReader::onNotify(
            Observable& sender_ __attribute__((unused)),
            ObservableEvent::E event_,
            void *context_ __attribute__((unused))) {

        if(event_!=ObservableEvent::USART_ReadyToTransmit)
            return;

        // send the byte

        USART_SendData(_writer.getUsartPeripheral(),_inputStream.read());

        // if no more data is available in the input stream, disable further sending

        if(!_inputStream.available())
            _writer.disableInterrupt();
    }

}
