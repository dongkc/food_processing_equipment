/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include <cstdlib>
#include "filesystem/fat/WearResistFreeClusterFinder.h"

namespace stm32plus {
    namespace fat {

        /**
         * Constructor: generate a random starting index between zero and the number of FAT entries.
         *
         * @param[in] fs_ A reference to the fat file system class. Must stay in scope.
         */

        WearResistFreeClusterFinder::WearResistFreeClusterFinder(FatFileSystem& fs_) :
            IteratingFreeClusterFinder(fs_,rand()%(fs_.getSectorsPerFat()*fs_.getSectorSizeInBytes())/fs_.getFatEntrySizeInBytes()) {
        }
    }
}
