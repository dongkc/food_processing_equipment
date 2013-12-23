/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include <stdint.h>

namespace stm32plus {

    /**
     * base class for FSMC implementations
     */

    class Fsmc {

        protected:
            uint32_t _bank;
            void *_baseAddress;

        protected:
            void initNE();

        public:
            Fsmc(uint32_t bank);
            void *getBaseAddress() const;
    };
}
