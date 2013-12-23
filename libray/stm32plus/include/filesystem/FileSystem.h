/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include <stdint.h>
#include "device/BlockDevice.h"
#include "timing/TimeProvider.h"
#include "filesystem/File.h"
#include "filesystem/FileInformation.h"
#include "filesystem/DirectoryIterator.h"

namespace stm32plus {

    /**
     * @brief File system base class.
     *
     * All file systems that derive from this use the same Unix style pathnames for addressing files. That is,
     * forward slashes as separators with / as the root. e.g. "/FileInRootDirectory.txt" or "/subdir/My Documents".
     * None of the filesystems support multibyte characters as filenames.
     */

    class FileSystem {

        protected:
            uint32_t _firstSectorIndex;
            uint32_t _sectorsPerBlock;
            BlockDevice& _blockDevice;
            const TimeProvider& _timeProvider;

        protected:
            FileSystem(BlockDevice& blockDevice_,const TimeProvider& timeProvider_,uint32_t firstSectorIndex_);

            uint32_t sectorIndexToBlockIndex(uint32_t sectorIndex_) const; // Convert a sector index to a block index
            uint32_t sectorOffsetIntoBlock(uint32_t sectorIndex_) const; // Get the byte offset into a block of the sector

        public:

            /**
             * Error codes
             */
            enum {
                /// Filesystem type is not known
                E_UNKNOWN_FILESYSTEM=1,

                /// Pathname is invalid
                E_INVALID_PATHNAME,

                /// Device block size and filesystem sector size are not the same
                E_UNEQUAL_BLOCK_SECTOR_SIZES,

                /// File already exists
                E_FILE_EXISTS,

                /// invalid block size
                E_INVALID_BLOCK_SIZE
            };


            /**
             * Possible file system types
             */

            enum FileSystemType {
                /// FAT16 filesystem
                Fat16,

                /// FAT32 filesystem
                Fat32
            };

        public:
            static bool getInstance(BlockDevice& blockDevice_,const TimeProvider& timeProvider_,FileSystem*& newFileSystem_);

            virtual ~FileSystem();

            const TimeProvider& getTimeProvider() const;

            virtual bool readSector(uint32_t sectorIndex_,void *buffer_);
            virtual bool writeSector(uint32_t sectorIndex,void *buffer_);

            /**
             * Get the first sector index
             * @return the index of the first sector on the device
             */

            uint32_t getFirstSector() const {
                return _firstSectorIndex;
            }

            /**
             * Get the type of the file system from the enumeration.
             * @return The file system type.
             */

            virtual FileSystemType getFileSystemType() const=0;


            /**
             * Get file information for the given pathname.
             *
             * @param[in] filename_ The full pathname of the file to get information for.
             * @param[out] finfo_ The information for this file. Caller must delete when finished.
             * @return false if it fails.
             */

            virtual bool getFileInformation(const char *filename_,FileInformation*& finfo_)=0;


            /**
             * Create a file at the given pathname. The file must not already exist. The newly created
             * file is available for opening afterwards and will have zero length.
             *
             * @param[in] filename_ The filename to create.
             * @return false if it fails.
             */

            virtual bool createFile(const char *filename_)=0;


            /**
             * Create a new directory at the given pathname.
             * @param[in] dirname_ The new directory name.
             * @return false if it fails.
             */

            virtual bool createDirectory(const char *dirname_)=0;


            /**
             * Open the file at the given pathname.
             * @param[in] filename_ The full pathname to an existing file.
             * @param[out] newFile_ The new File object that the caller can use. Caller must delete when finished.
             * @return false if it fails.
             */

            virtual bool openFile(const char *filename_,File*& newFile_)=0;


            /**
             * Delete the file at the given pathname.
             * @param[in] filename_ The filename to delete.
             * @return false if it fails.
             */

            virtual bool deleteFile(const char *filename_)=0;


            /**
             * Delete the directory with the given name. The directory must be empty.
             * @param[in] dirname_ The directory to delete.
             * @return false if it fails.
             */

            virtual bool deleteDirectory(const char *dirname_)=0;

            /**
             * Get the size of a sector on this file system. Usually 512.
             * @return The sector size.
             */

            virtual uint32_t getSectorSizeInBytes() const=0;

            /**
             * Get a directory iterator on to the given directory.
             * @param[in] pathname_ The pathname to the directory to open.
             * @param[out] newIterator_ A new iterator for the caller to use. Caller must delete when finished.
             * @return false if it fails.
             */

            virtual bool getDirectoryIterator(const char *pathname_,DirectoryIterator*& newIterator_)=0;


            /**
             * Get the free space on the device as a two part result. The free space in bytes
             * Can be found by multiplying the two results together.
           * @param[out] freeUnits_ The number of free units.
           * @param[out] unitsMultiplier_ What to multiply freeUnits_ by to get a byte size.
           * @return false if it fails.
           */

            virtual bool getFreeSpace(uint32_t& freeUnits_,uint32_t& unitsMultiplier_)=0;
    };
}
