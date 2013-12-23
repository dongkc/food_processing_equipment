/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "filesystem/fat/FatFileSystemFormatter.h"
#include "filesystem/fat/Fat32FsInfo.h"


namespace stm32plus {
    namespace fat {


    /**
     * @brief Formatter for fat32 file systems.
     */

        class Fat32FileSystemFormatter : public FatFileSystemFormatter {

            protected:
                virtual bool createNewBootSector();
                virtual bool writeReservedSectors();
                virtual void initReservedClusters(uint8_t *sector) const;

                void createNewFsInfo(Fat32FsInfo& fsinfo_) const;

            public:
                Fat32FileSystemFormatter(BlockDevice& blockDevice,uint32_t firstSectorIndex,uint32_t numSectors,const char *volumeLabel);
                virtual ~Fat32FileSystemFormatter() {}
        };

    }
}
