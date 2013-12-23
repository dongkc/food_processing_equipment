/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "filesystem/fat/FatFileSystemFormatter.h"


namespace stm32plus {
    namespace fat {

        /**
         * @brief Implementation of a FAT formatter for FAT16 file systems
         */

        class Fat16FileSystemFormatter : public FatFileSystemFormatter {

            protected:
              virtual bool createNewBootSector();
              virtual bool writeReservedSectors();
              virtual void initReservedClusters(uint8_t *sector_) const;

            public:
              Fat16FileSystemFormatter(BlockDevice& blockDevice_,uint32_t firstSectorIndex_,uint32_t numSectors_,const char *volumeLabel_);
        };
    }
}
