/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include <stdint.h>
#include "filesystem/fat/FatFileSystem.h"
#include "filesystem/fat/ClusterChainIterator.h"
#include "memory/Memblock.h"
#include "iterator/Iterator.h"

namespace stm32plus {
    namespace fat {

        /**
         * @brief Iterate through the sectors of a file
         */

        class FileSectorIterator : public Iterator<uint32_t> {

            protected:
                ClusterChainIterator _iterator;
                FatFileSystem& _fs;
                uint32_t _sectorIndexInCluster;
                uint32_t _sectorsPerCluster;

            public:
                FileSectorIterator(FatFileSystem& fs_,uint32_t firstClusterIndex_,ClusterChainIterator::ExtensionMode extend_);

                /**
                 * Virtual destructor, does nothing.
                 */

                virtual ~FileSectorIterator() {
                }

                uint32_t getClusterNumber();

                bool readSector(void *buffer_);
                bool writeSector(void *buffer_);

                void reset(uint32_t firstClusterNumber_);

                // overrides from Iterator

                virtual bool next();
                virtual uint32_t current();
        };

    }
}
