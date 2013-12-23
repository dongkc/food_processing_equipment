/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "filesystem/TokenisedPathname.h"

namespace stm32plus {

    /**
     * Constructor
     * @param[in] pathname_ The pathname to tokenise.
     */

    TokenisedPathname::TokenisedPathname(const char *pathname_) :
        TokenisedString(pathname_,"\\/") {
    }
}
