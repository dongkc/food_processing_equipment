/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "filesystem/fat/FatFileSystem.h"
#include "filesystem/fat/DirectoryEntryIterator.h"


namespace stm32plus {
    namespace fat {

    /**
     * @brief FAT32 implementation of the filesystem.
     *
     * Provides an implementation of FatFileSystem for FAT32.
     */

        class Fat32FileSystem : public FatFileSystem {

            public:
                Fat32FileSystem(
          BlockDevice& blockDevice_,
          const TimeProvider& timeProvider_,
          const fat::BootSector& bootSector_,
          uint32_t firstSectorIndex_,
          uint32_t countOfClusters_);
                
        virtual ~Fat32FileSystem();

            // overrides from FatFileSystem

                virtual FileSystemType getFileSystemType() const;
                virtual uint32_t getFatEntrySizeInBytes() const;
                virtual uint32_t getBadClusterMarker() const;
                virtual uint32_t getFatEntryFromMemory(void *addr_) const;
                virtual void setFatEntryToMemory(void *addr_,uint32_t entry_) const;
                virtual uint32_t getSectorsPerFat() const;
                virtual bool isEndOfClusterChainMarker(uint32_t clusterNumber_) const;
                virtual uint32_t getEndOfClusterChainMarker() const;
                virtual DirectoryEntryIterator *getRootDirectoryIterator(DirectoryEntryIterator::Options options_);
        };
    }
}
