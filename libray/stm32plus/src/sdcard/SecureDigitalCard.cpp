/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "sdcard/SecureDigitalCard.h"


extern SD_CardInfo SDCardInfo;


namespace stm32plus {


    /**
     * Get the CSD structure.
     * @return a reference to the CSD structure.
     */

    const SD_CSD& SecureDigitalCard::getCsd() const {
        return SDCardInfo.SD_csd;
    }


    /**
     * Get the CID structure
     * @return A reference to the CID structure.
     */

    const SD_CID& SecureDigitalCard::getCid() const {
        return SDCardInfo.SD_cid;
    }


    /**
     * Get the total number of blocks on this card.
     * @return The total number of blocks
     */

    uint32_t SecureDigitalCard::getTotalBlocksOnDevice() {
        return getCardCapacityInBytes()/getBlockSizeInBytes();
    }



    /**
     * Get the device format type
     * @return An enumeration that tells you whether this device has a Master Boot Record (MBR) or not.
     */

    BlockDevice::formatType SecureDigitalCard::getFormatType() {

        switch(SDCardInfo.SD_csd.FileFormat) {

            case 0:
                return formatMbr;

            case 1:
                return formatNoMbr;

            default:
                return formatUnknown;
        }
    }

}
