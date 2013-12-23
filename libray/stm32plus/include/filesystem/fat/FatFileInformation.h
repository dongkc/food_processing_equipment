/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "filesystem/FileInformation.h"
#include "filesystem/fat/DirectoryEntryWithLocation.h"

namespace stm32plus {
    namespace fat {

        /**
         * @brief Extended file information to include the FAT-specific DirectoryEntry
         */

        class FatFileInformation : public FileInformation {

            protected:
                uint32_t _attributes;
                const char *_filename;
                time_t _creationDate;
                time_t _lastWriteDateTime;
                time_t _lastAccessDateTime;
                uint32_t _length;

            public:
                /**
                 * Default constructor. Do nothing.
                 */

                FatFileInformation() {
                }

                FatFileInformation(const char *filename_,const DirectoryEntryWithLocation& dirent_);

                /**
                 * Virtual destructor. Do nothing.
                 */

                virtual ~FatFileInformation() {
                }

                // overrides from FileInformation

                virtual uint32_t getAttributes() const;
                virtual const char *getFilename() const;
                virtual time_t getCreationDateTime() const;
                virtual time_t getLastWriteDateTime() const;
                virtual time_t getLastAccessDateTime() const;
                virtual uint32_t getLength() const;
        };
    }
}
