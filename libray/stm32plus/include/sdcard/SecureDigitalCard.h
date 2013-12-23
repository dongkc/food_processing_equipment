/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "device/BlockDevice.h"
#include "stm32_eval_sdio_sd.h"


namespace stm32plus {

    /**
     * @brief Base class for secure digital implementations
     */

    class SecureDigitalCard : public BlockDevice {

        public:
            virtual formatType getFormatType();

            const SD_CSD& getCsd() const;
            const SD_CID& getCid() const;

            /**
             * Do-nothing virtual destructor
             */

            virtual ~SecureDigitalCard() {}


            virtual uint32_t getTotalBlocksOnDevice();


            /**
             * Get the block size of the card in bytes
             * @return The block size.
             */

            virtual uint32_t getBlockSizeInBytes()=0;


            /**
             * Get the card capacity in bytes.
             * @return The card capacity.
             */

            virtual uint32_t getCardCapacityInBytes()=0;

            /**
             * Read a single block.
             * @param[in,out] dest_ The memory buffer to read to.
             * @param[in] blockIndex_ The block index to read.
             * @return false if it fails.
             */

            virtual bool readBlock(void *dest_,uint32_t blockIndex_)=0;

            /**
             * Read a number of blocks.
             * @param[in,out] dest_ The memory buffer to read to.
             * @param[in] blockIndex_ The first block index to read.
             * @param[in] numBlocks_ The number of blocks to read.
             * @return false if it fails.
             */

            virtual bool readBlocks(void *dest_,uint32_t blockIndex_,uint32_t numBlocks_)=0;

            /**
             * Write a single block.
             * @param[in] dest_ The memory buffer to write from
             * @param[in] blockIndex_ The block index to write.
             * @return false if it fails.
             */

            virtual bool writeBlock(void *dest_,uint32_t blockIndex_)=0;

            /**
             * Write a number of blocks.
             * @param[in] dest_ The memory buffer to write from.
             * @param[in] blockIndex_ The first block index to write.
             * @param[in] numBlocks_ The number of blocks to write.
             * @return false if it fails.
             */

            virtual bool writeBlocks(void *dest_,uint32_t blockIndex_,uint32_t numBlocks_)=0;

            /**
             * Erase a number of blocks.
             * @param[in] blockIndex_ The first block index to erase.
             * @param[in] numBlocks_ The number of blocks to erase.
             * @return false if it fails.
             */

            virtual bool eraseBlocks(uint32_t blockIndex_,uint32_t numBlocks_)=0;
    };
}
