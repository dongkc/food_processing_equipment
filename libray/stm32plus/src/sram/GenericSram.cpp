/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "sram/GenericSram.h"
#include "memory/MEM_DataCopy.h"
#include "error/ErrorProvider.h"


namespace stm32plus {


    /**
     * Constructor. Initialise the device
     */

    GenericSram::GenericSram(uint32_t bank,const FsmcSramTiming& timing,const uint32_t lastAddressLineIndex)
        : FsmcSram(bank,timing,lastAddressLineIndex) {

        // the bank of SRAM is not volatile (does not contain peripheral registers)

        _sramStartAddress=static_cast<uint8_t *>(_baseAddress);
    }


    /*
     * Get the block size.
     * @return always 512
     */

    uint32_t GenericSram::getBlockSizeInBytes() {
        return BLOCK_SIZE;
    }


    /*
     * Read a single block
     */

    bool GenericSram::readBlock(void *dest,uint32_t blockIndex)  {
        MEM_DataCopy(dest,_sramStartAddress+(blockIndex * BLOCK_SIZE),BLOCK_SIZE);
        return true;
    }


    /*
     * Read many blocks
     */

    bool GenericSram::readBlocks(void *dest,uint32_t blockIndex,uint32_t numBlocks) {
        MEM_DataCopy(dest,_sramStartAddress+(blockIndex * BLOCK_SIZE),numBlocks * BLOCK_SIZE);
        return true;
    }


    /*
     * Write a block
     */

    bool GenericSram::writeBlock(void *dest,uint32_t blockIndex) {
        MEM_DataCopy(_sramStartAddress+(blockIndex * BLOCK_SIZE),dest,BLOCK_SIZE);
        return true;
    }


    /*
     * Write many blocks
     */

    bool GenericSram::writeBlocks(void *dest,uint32_t blockIndex,uint32_t numBlocks) {
        MEM_DataCopy(_sramStartAddress+(blockIndex * BLOCK_SIZE),dest,numBlocks * BLOCK_SIZE);
        return true;
    }


    /*
     * Get the format type - no MBR
     */

    BlockDevice::formatType GenericSram::getFormatType() {
        return BlockDevice::formatNoMbr;
    }


    /*
     * Cannot get the MBR
     */

    bool GenericSram::getMbr(Mbr *mbr __attribute((unused))) {
        return errorProvider.set(ErrorProvider::ERROR_PROVIDER_SRAM,E_NO_MBR);
    }
}
