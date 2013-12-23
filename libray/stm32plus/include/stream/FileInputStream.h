/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "stream/InputStream.h"
#include "filesystem/FileSystem.h"
#include "filesystem/File.h"

namespace stm32plus {

    /**
     * @brief Implementation of an input stream for files
     */

    class FileInputStream : public InputStream {
        protected:
            File& _file;

        public:
            FileInputStream(File& f_);
            virtual ~FileInputStream() {}

        public:

            // overrides from InputStream

            virtual int16_t read();
            virtual bool read(void *buffer,uint32_t size_,uint32_t& actuallyRead_);
            virtual bool close();
            virtual bool skip(uint32_t howMuch_);
            virtual bool available();
            virtual bool reset();
    };
}
