/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#pragma once

#include "BlockDevice.h"

namespace stm32plus {

    /**
     * @brief Specialisation of BlockDevice to provide in-memory caching.
     *
     * This class subclasses BlockDevice and provides in-memory caching of recently
     * used blocks. The cache is write-through. A user of this class must ensure
     * that he has enough RAM in his device to support the desired cache size.
     */

    class CachedBlockDevice : public BlockDevice {

        protected:

            struct CacheEntry {
                    uint32_t BlockIndex;
                    uint32_t CacheIndex;
            };

            BlockDevice& _device;
            uint32_t _numCachedBlocks;
            uint8_t **_cachedBlocks;
            CacheEntry *_cacheIndex;
            uint32_t _blockSize;

            static const uint32_t FREE_CACHE_ENTRY=0xFFFFFFFF;

        protected:
            void writeToCache(void *data_,uint32_t blockIndex_);
            void moveToFront(uint32_t index_);

        public:
            CachedBlockDevice(BlockDevice& bd_,uint32_t numCachedBlocks_);
            virtual ~CachedBlockDevice();

            // overrides from BlockDevice

            virtual uint32_t getBlockSizeInBytes();

            virtual bool readBlock(void *pDest_,uint32_t blockIndex_);
            virtual bool readBlocks(void *pDest_,uint32_t blockIndex_,uint32_t numBlocks_);

            virtual bool writeBlock(void *pDest_,uint32_t blockIndex_);
            virtual bool writeBlocks(void *pDest_,uint32_t blockIndex_,uint32_t numBlocks_);

            virtual uint32_t getTotalBlocksOnDevice();

            virtual formatType getFormatType();
    };
}

