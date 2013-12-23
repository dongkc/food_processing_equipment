/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include <stdint.h>


/*
 * Various string utilities
 */

namespace stm32plus {
    namespace StringUtil {

        char* itoa(int value,char* result,int base);
        uint32_t modp_uitoa10(uint32_t value,char *str);
        uint16_t modp_dtoa(double value,int8_t prec,char *str);
    }
}
