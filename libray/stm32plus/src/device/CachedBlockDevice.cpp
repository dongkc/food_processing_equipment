/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include <cstring>
#include "device/CachedBlockDevice.h"
#include "memory/MEM_DataCopy.h"


namespace stm32plus {

    /**
     * Constructor
     *
     * @param[in] bd_ The block device being cached. Must not go out of scope.
     * @param[in] numCachedBlocks_ The number of blocks to cache. This parameter controls the memory used by this class.
     */

    CachedBlockDevice::CachedBlockDevice(BlockDevice& bd_,uint32_t numCachedBlocks_) :
        _device(bd_), _numCachedBlocks(numCachedBlocks_), _blockSize(bd_.getBlockSizeInBytes()) {
        uint32_t i;

        _cachedBlocks=new uint8_t *[numCachedBlocks_];
        _cacheIndex=new CacheEntry[numCachedBlocks_];

        for(i=0;i<numCachedBlocks_;i++) {
            _cachedBlocks[i]=new uint8_t[_blockSize];
            _cacheIndex[i].BlockIndex=FREE_CACHE_ENTRY;
            _cacheIndex[i].CacheIndex=i;
        }
    }

    /**
     * Destructor. Free memory allocated by the cache.
     */

    CachedBlockDevice::~CachedBlockDevice() {

        uint32_t i;

        for(i=0;i<_numCachedBlocks;i++)
            delete[] _cachedBlocks[i];

        delete _cachedBlocks;
        delete _cacheIndex;
    }

    /*
     * read a block
     */

    bool CachedBlockDevice::readBlock(void *pDest_,uint32_t blockIndex_) {

        uint32_t i;

        // try to find in the cache index

        for(i=0;i<_numCachedBlocks&&_cacheIndex[i].BlockIndex!=FREE_CACHE_ENTRY;i++) {

            if(_cacheIndex[i].BlockIndex==blockIndex_) {

                // cache hit

                MEM_DataCopy(pDest_,_cachedBlocks[_cacheIndex[i].CacheIndex],_blockSize);
                moveToFront(i);
                return true;
            }
        }

        // cache miss, read from device

        if(!_device.readBlock(pDest_,blockIndex_))
            return false;

        // write to the cache

        writeToCache(pDest_,blockIndex_);
        return true;
    }

    /*
     * write a block
     */

    bool CachedBlockDevice::writeBlock(void *pDest_,uint32_t blockIndex_) {

        // write through

        if(!_device.writeBlock(pDest_,blockIndex_))
            return false;

        // and into the cache

        writeToCache(pDest_,blockIndex_);
        return true;
    }

    /*
     * find cache entry and write
     */

    void CachedBlockDevice::writeToCache(void *data_,uint32_t blockIndex_) {

        uint32_t i;
        CacheEntry evictedEntry;

        // if already in the cache index then move its entry to the front

        for(i=0;i<_numCachedBlocks&&_cacheIndex[i].BlockIndex!=FREE_CACHE_ENTRY;i++) {

            if(_cacheIndex[i].BlockIndex==blockIndex_) {
                moveToFront(i);
                MEM_DataCopy(_cachedBlocks[_cacheIndex[i].CacheIndex],data_,_blockSize);
                return;
            }
        }

        // move up the whole index losing the last one

        evictedEntry=_cacheIndex[_numCachedBlocks-1];
        memmove(&_cacheIndex[1],&_cacheIndex[0],sizeof(CacheEntry)*(_numCachedBlocks-1));

        // this is a new entry into the index so store its data

        MEM_DataCopy(_cachedBlocks[evictedEntry.CacheIndex],data_,_blockSize);

        evictedEntry.BlockIndex=blockIndex_;
        _cacheIndex[0]=evictedEntry;
    }

    /*
     * move an entry to the front of the index
     */

    void CachedBlockDevice::moveToFront(uint32_t index_) {

        if(index_!=0) {

            CacheEntry entry;

            entry=_cacheIndex[index_];
            memmove(&_cacheIndex[1],&_cacheIndex[0],sizeof(CacheEntry)*index_);
            _cacheIndex[0]=entry;
        }
    }

    /*
     * multi-block write
     */

    bool CachedBlockDevice::writeBlocks(void *pDest_,uint32_t blockIndex_,uint32_t numBlocks_) {

        uint32_t i;
        uint8_t *ptr;

        ptr=static_cast<uint8_t *> (pDest_);

        for(i=0;i<numBlocks_;i++) {

            if(!writeBlock(ptr,blockIndex_+i))
                return false;

            ptr+=_blockSize;
        }

        return true;
    }

    /*
     * multi-block read
     */

    bool CachedBlockDevice::readBlocks(void *pDest_,uint32_t blockIndex_,uint32_t numBlocks_) {
        uint32_t i;
        uint8_t *ptr;

        ptr=static_cast<uint8_t *> (pDest_);

        for(i=0;i<numBlocks_;i++) {

            if(!readBlock(ptr,blockIndex_+i))
                return false;

            ptr+=_blockSize;
        }

        return true;
    }

    /*
     * pass through to device
     */

    BlockDevice::formatType CachedBlockDevice::getFormatType() {
        return _device.getFormatType();
    }

    uint32_t CachedBlockDevice::getBlockSizeInBytes() {
        return _blockSize;
    }

    uint32_t CachedBlockDevice::getTotalBlocksOnDevice() {
        return _device.getTotalBlocksOnDevice();
    }
}
