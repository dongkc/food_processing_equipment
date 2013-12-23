/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "filesystem/fat/FreeClusterFinder.h"
#include "filesystem/fat/FatIterator.h"

namespace stm32plus {
    namespace fat {

        /**
         * @brief Free cluster finder that uses a FAT iterator to find free clusters.
         *
         * This is a base class
         */

        class IteratingFreeClusterFinder : public FreeClusterFinder {

            protected:
                FatIterator _iterator;

            protected:
                IteratingFreeClusterFinder(FatFileSystem& fs_,uint32_t firstFatEntry_);

            public:

            /**
             * Virtual destructor, does nothing
             */

                virtual ~IteratingFreeClusterFinder() {
                }

                virtual bool find(uint32_t& freeCluster_);
        };

    }
}
