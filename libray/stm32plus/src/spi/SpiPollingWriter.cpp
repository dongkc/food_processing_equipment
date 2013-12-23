/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#include "spi/SpiPollingWriter.h"


namespace stm32plus {

    /**
     * Constructor
     * @param[in] peripheral The SPI peripheral to write to
     */

    SpiPollingWriter::SpiPollingWriter(SpiPeripheral& peripheral)
        : SpiWriter(peripheral) {
    }



    /**
     * Write a block of bytes, blocking.
     */

    bool SpiPollingWriter::write(uint8_t *dataToSend,uint32_t numBytes,uint8_t *dataReceived) {

        // wait for ready to send

        while(numBytes--) {

            while(!readyToSend())
                if(_peripheral.hasError())
                    return false;

            // send the byte

            SPI_I2S_SendData(_peripheral,*dataToSend++);

            if(_duplex) {

                // in duplex mode and we want data, wait for it to come

                while(SPI_I2S_GetFlagStatus(_peripheral,SPI_I2S_FLAG_RXNE)==RESET)
                    if(_peripheral.hasError())
                        return false;

                // read the byte to clear RXNE and save/discard

                if(dataReceived!=NULL)
                    *dataReceived++=SPI_I2S_ReceiveData(_peripheral);
                else
                    SPI_I2S_ReceiveData(_peripheral);
            }
        }

        return true;
    }
}
