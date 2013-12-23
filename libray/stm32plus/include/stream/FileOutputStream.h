/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include <stdint.h>
#include "stream/OutputStream.h"
#include "filesystem/FileSystem.h"
#include "filesystem/File.h"

namespace stm32plus {

    /**
     * @brief Implementation of an output stream for files
     */

    class FileOutputStream : public OutputStream {
        protected:
            File& _file;

        public:
            FileOutputStream(File& f_);

        public:

            // overrides from OutputStream

            virtual bool write(uint8_t c_);
            virtual bool write(const void *buffer,uint32_t size_);
            virtual bool close();

            virtual bool flush() {
                return true;
            }
    };
}
