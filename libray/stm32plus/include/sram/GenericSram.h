/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "fsmc/FsmcSram.h"
#include "device/BlockDevice.h"


namespace stm32plus {

    /**
     * @brief Generic implementation of the SRAM interface
     */

    class GenericSram : public FsmcSram,
                                            public BlockDevice {

        protected:
            static const uint32_t BLOCK_SIZE = 512;

            uint8_t *_sramStartAddress;

            /**
             * Error codes
             */

            enum {
                /// SRAM block device has no MBR
                E_NO_MBR = 1
            };

        public:
            GenericSram(uint32_t bank,const FsmcSramTiming& timing,const uint32_t lastAddressLineIndex);
            virtual ~GenericSram() {}

            // overrides from BlockDevice

            virtual uint32_t getBlockSizeInBytes();
            virtual bool readBlock(void *dest,uint32_t blockIndex);
            virtual bool readBlocks(void *dest,uint32_t blockIndex,uint32_t numBlocks);
            virtual bool writeBlock(void *dest,uint32_t blockIndex);
            virtual bool writeBlocks(void *dest,uint32_t blockIndex,uint32_t numBlocks);
            virtual formatType getFormatType();
            virtual bool getMbr(Mbr *mbr);

            /**
             * Cast to a void * for user access
             */

            operator void *() {
                return _sramStartAddress;
            }
    };
}
