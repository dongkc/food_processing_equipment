/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "filesystem/DirectoryIterator.h"
#include "filesystem/fat/FatFileSystem.h"
#include "filesystem/fat/FatFileInformation.h"
#include "filesystem/TokenisedPathname.h"


namespace stm32plus {
    namespace fat {

    /**
     * @brief Base class for iterating over the entries in a FAT directory.
     *
     * This class provides the static factory method used for returning an appropriate
     * derived class.
     */

        class FatDirectoryIterator : public DirectoryIterator, public FatFileInformation {

            protected:
                FatFileSystem& _fs;
                DirectoryEntryIterator *_entryIterator;

            protected:
                FatDirectoryIterator(FatFileSystem& fs,DirectoryEntryWithLocation& dirent);
                FatDirectoryIterator(FatFileSystem& fs);

            public:
                static bool getInstance(FatFileSystem& fs,const TokenisedPathname& tp,FatDirectoryIterator *& newIterator);

                virtual ~FatDirectoryIterator();

        DirectoryEntryIterator& getDirectoryEntryIterator();

            // overrides from Iterator<FileInformation>

                virtual bool next();
                virtual const FileInformation& current();

            // overrides from DirectoryIterator

                virtual bool getSubdirectoryIterator(DirectoryIterator *& newIterator);
                virtual bool isCurrentDirectory();
                virtual bool isParentDirectory();
                virtual bool moveTo(const char *filename);
                virtual bool openFile(File*& newFile);

            // overrides from FileInformation

                virtual const char *getFilename() const;
                virtual uint32_t getAttributes() const;
                virtual time_t getCreationDateTime() const;
                virtual time_t getLastWriteDateTime() const;
                virtual time_t getLastAccessDateTime() const;
                virtual uint32_t getLength() const;

            // overrides from FatFileInformation

                DirectoryEntryWithLocation& getDirectoryEntryWithLocation();
        };
    }
}
