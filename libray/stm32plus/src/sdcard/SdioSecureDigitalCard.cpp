/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "sdcard/SdioSecureDigitalCard.h"
#include "error/ErrorProvider.h"
#include "config/stdperiph.h"
#include "config/interrupts.h"
#include "gpio/GpioPort.h"
#include "nvic/Nvic.h"
#include "sdcard/stm32_eval_sdio_sd.h"


extern SD_CardInfo SDCardInfo;

namespace stm32plus {

    /**
     * Constructor. Enables the SDIO IRQ, initialises GPIO and clocks and initialises the peripheral. Note that
     * this constructor can set an error in the errorProvider if initialisation fails. Callers should check the
     * error status before attempting to use this.
     */

    SdioSecureDigitalCard::SdioSecureDigitalCard() {

        Nvic::configureIrq(SDIO_IRQn);

        errorProvider.clear();

        // initialise the peripheral
        initialisePeripheral();

        // configure peripheral
        SD_Init();
    }


    /*
     * Start clock and set GPIO
     */

    void SdioSecureDigitalCard::initialisePeripheral() const {

        GpioPort pc(GPIOC),pd(GPIOD),pf(GPIOF);

        // GPIO ports for the peripheral

        pc.initialise(
                GPIO_Speed_50MHz,
                GPIO_Mode_AF_PP,
                GPIO_Pin_8 |                // DO
                GPIO_Pin_9 |                 // D1
                GPIO_Pin_10 |             // D2
                GPIO_Pin_11    |                // D3
                GPIO_Pin_12                    // SDIO_SCK
            );

        pd.initialise(
                GPIO_Speed_50MHz,
                GPIO_Mode_AF_PP,
                GPIO_Pin_2                    // SDIO_CMD
            );

        // clocks for SDIO and its DMA channel

        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SDIO | RCC_AHBPeriph_DMA2, ENABLE);
    }

    /*
     * Get block size in bytes
     */

    uint32_t SdioSecureDigitalCard::getBlockSizeInBytes() {
        return BlockSize;
    }

    /*
     * Get the card capacity in bytes
     */

    uint32_t SdioSecureDigitalCard::getCardCapacityInBytes() {
        return SDCardInfo.CardCapacity;
    }

    /*
     * Read a block
     */

    bool SdioSecureDigitalCard::readBlock(void *pDest_,uint32_t blockIndex_) {
        return handleReadReturn(SD_ReadBlock(static_cast<uint8_t *> (pDest_),blockIndex_,getBlockSizeInBytes()),E_FAILED_TO_READ_BLOCK);
    }

    /*
     * Read multiple blocks
     */

    bool SdioSecureDigitalCard::readBlocks(void *pDest_,uint32_t blockIndex_,uint32_t numBlocks_) {
        return handleReadReturn(SD_ReadMultiBlocks(static_cast<uint8_t *> (pDest_),blockIndex_,getBlockSizeInBytes(),numBlocks_),E_FAILED_TO_READ_MULTIBLOCK);
    }

    /*
     * Write a single block
     */

    bool SdioSecureDigitalCard::writeBlock(void *pDest_,uint32_t blockIndex_) {
        return handleWriteReturn(SD_WriteBlock(static_cast<uint8_t *> (pDest_),blockIndex_,getBlockSizeInBytes()),E_FAILED_TO_WRITE_BLOCK);
    }

    /*
     * Write many blocks
     */

    bool SdioSecureDigitalCard::writeBlocks(void *pDest_,uint32_t blockIndex_,uint32_t numBlocks_) {
        return handleWriteReturn(SD_WriteMultiBlocks(static_cast<uint8_t *> (pDest_),blockIndex_,getBlockSizeInBytes(),numBlocks_),E_FAILED_TO_WRITE_MULTIBLOCK);
    }

    /*
     * Erase many blocks
     */

    bool SdioSecureDigitalCard::eraseBlocks(uint32_t blockIndex_,uint32_t numBlocks_) {

        uint32_t startAddr,endAddr;

        startAddr=blockIndex_ * getBlockSizeInBytes();
        endAddr=startAddr + (getBlockSizeInBytes() * numBlocks_);

        return handleReturnCode(SD_Erase(startAddr,endAddr),E_FAILED_TO_ERASE_BLOCKS);
    }


    /*
     * Handle return from a read operation
     */

    bool SdioSecureDigitalCard::handleReadReturn(SD_Error sdError,uint32_t errorCode) {

        if(sdError==SD_OK) {

            if((sdError=SD_WaitReadOperation())!=SD_OK)
                return handleReturnCode(sdError,errorCode);

            while(SD_GetStatus() != SD_TRANSFER_OK);
            return true;
        }
        else
            return handleReturnCode(sdError,errorCode);
    }


    /*
     * Handle return from a write operation
     */

    bool SdioSecureDigitalCard::handleWriteReturn(SD_Error sdError,uint32_t errorCode) {

        if(sdError==SD_OK) {

            if((sdError=SD_WaitWriteOperation())!=SD_OK)
                return handleReturnCode(sdError,errorCode);

            while(SD_GetStatus()!=SD_TRANSFER_OK);
            return true;
        }
        else
            return handleReturnCode(sdError,errorCode);
    }


    /*
     * Handle a return code
     */

    bool SdioSecureDigitalCard::handleReturnCode(SD_Error sdError,uint32_t errorCode) {

        if(sdError == SD_OK) {
            errorProvider.clear();
            return true;
        } else
            return errorProvider.set(ErrorProvider::ERROR_PROVIDER_SD_SDIO,errorCode,sdError);
    }

}


/*
 * IRQ handler for SDIO interrupts
 */

extern "C" {

    #if defined(USE_SDIO_INTERRUPT)

    void SDIO_IRQHandler(void) {
        SD_ProcessIRQSrc();
    }

    #endif

}

