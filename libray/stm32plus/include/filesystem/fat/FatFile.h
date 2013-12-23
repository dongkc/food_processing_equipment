/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include <stdint.h>
#include "filesystem/File.h"
#include "filesystem/fat/DirectoryEntryWithLocation.h"
#include "filesystem/fat/FatFileSystem.h"
#include "memory/Memblock.h"
#include "filesystem/fat//FileSectorIterator.h"


namespace stm32plus {
    namespace fat {

        /**
         * @brief Fat file extends the basic File class.
         *
         * FAT implementation of the File base class.
         */

        class FatFile : public File {
            protected:
                FatFileSystem& _fs;
                DirectoryEntryWithLocation _dirent;
                ByteMemblock _sectorBuffer;
                FileSectorIterator _iterator;

            protected:
                void calcIndexes();

            public:
                FatFile(FatFileSystem& fs_,DirectoryEntryWithLocation& dirent_);

                /**
                 * Virtual destructor, does nothing.
                 */

                virtual ~FatFile() {}

      // get the dirent

        const DirectoryEntryWithLocation& getDirectoryEntryWithLocation();

            // overrides from File

                virtual bool read(void *ptr_,uint32_t size_,uint32_t& actuallyRead_);
                virtual bool write(const void *ptr_,uint32_t size_);
                virtual bool seek(int32_t offset_,SeekFrom origin_);
                virtual uint32_t getLength();
        };
    }
}
