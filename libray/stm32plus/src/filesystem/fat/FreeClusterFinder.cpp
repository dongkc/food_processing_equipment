/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "filesystem/fat/FreeClusterFinder.h"

namespace stm32plus {
    namespace fat {

        /*
         * Constructor
         */

        FreeClusterFinder::FreeClusterFinder(FatFileSystem& fs_) :
            _fs(fs_) {
        }
    }
}
