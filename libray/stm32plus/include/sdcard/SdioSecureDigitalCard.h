/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "SecureDigitalCard.h"
#include "stm32_eval_sdio_sd.h"


namespace stm32plus {

    /**
     * @brief SDIO interface to the secure digital card
     */

    class SdioSecureDigitalCard : public SecureDigitalCard {

        protected:
            enum { BlockSize=512 };

        protected:
            bool handleReturnCode(SD_Error sdError_,uint32_t errorCode_);
            void initialisePeripheral() const;
            bool handleReadReturn(SD_Error sdError,uint32_t errorCode);
            bool handleWriteReturn(SD_Error sdError,uint32_t errorCode);

        public:

            /**
             * Error codes. The SD operations all return a provider-specific error code in addition to the
             * more generic codes offered here.
             */

            enum {

                /// The SD card failed to initialise
                E_FAILED_TO_INITIALISE = 1,

                /// A block read operation failed
                E_FAILED_TO_READ_BLOCK,

                /// A block write operation failed
                E_FAILED_TO_WRITE_BLOCK,

                /// A multi-block read operation failed
                E_FAILED_TO_READ_MULTIBLOCK,

                /// A multi-block write operation failed
                E_FAILED_TO_WRITE_MULTIBLOCK,

                /// An erase operation failed
                E_FAILED_TO_ERASE_BLOCKS
            };


            SdioSecureDigitalCard();
            virtual ~SdioSecureDigitalCard() {}

            // overrides from SecureDigital card

            virtual uint32_t getBlockSizeInBytes();
            virtual uint32_t getCardCapacityInBytes();

            virtual bool readBlock(void *pDest_,uint32_t blockIndex_);
            virtual bool readBlocks(void *pDest_,uint32_t blockIndex_,uint32_t numBlocks_);

            virtual bool writeBlock(void *pDest_,uint32_t blockIndex_);
            virtual bool writeBlocks(void *pDest_,uint32_t blockIndex_,uint32_t numBlocks_);

            virtual bool eraseBlocks(uint32_t blockIndex_,uint32_t numBlocks_);
    };
}
