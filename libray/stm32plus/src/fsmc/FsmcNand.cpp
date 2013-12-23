/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "fsmc/FsmcNand.h"
#include "gpio/GpioPort.h"


namespace stm32plus {

    /**
     * Constructor. Setup the FSMC ready for use
     */

    FsmcNand::FsmcNand(uint32_t bank,const FsmcNandTiming& timing)
        : Fsmc(bank) {

        GpioPort pd(GPIOD),pe(GPIOE),pg(GPIOG);

        // port D alternate function initialisation

        pd.initialise(
                GPIO_Speed_50MHz,
                GPIO_Mode_AF_PP,
                GPIO_Pin_0 |                // D2
                GPIO_Pin_1 |                // D3
                GPIO_Pin_4 |                // nOE
                GPIO_Pin_5 |                // nWE
                GPIO_Pin_7 |                // NE2
                GPIO_Pin_11 |                // CLE
                GPIO_Pin_12 |                // ALE
                GPIO_Pin_14 |                // D0
                GPIO_Pin_15);                // D1

        // port E alternate function initialisation

        pe.initialise(
                GPIO_Speed_50MHz,
                GPIO_Mode_AF_PP,
                GPIO_Pin_7 |                // D4
                GPIO_Pin_8 |                 // D5
                GPIO_Pin_9 |                 // D6
                GPIO_Pin_10);                // D7

        // port D nWAIT input pin, pull up (nWAIT is active low)

        pd.initialise(
                GPIO_Speed_50MHz,
                GPIO_Mode_IPU,
                GPIO_Pin_6);                // nWAIT

        // port G IN2 input pin, pull up (nWAIT is active low)
        // not available on LQFP100

        pg.initialise(
                GPIO_Speed_50MHz,
                GPIO_Mode_IPU,
                GPIO_Pin_6);                // INT2

        // initialise how the FSMC will work

        FSMC_Bank=bank;
        FSMC_Waitfeature=FSMC_Waitfeature_Enable;
        FSMC_MemoryDataWidth=FSMC_MemoryDataWidth_8b;
        FSMC_ECC=FSMC_ECC_Enable;
        FSMC_ECCPageSize=FSMC_ECCPageSize_512Bytes;
        FSMC_TCLRSetupTime=0x00;
        FSMC_TARSetupTime=0x00;
        FSMC_CommonSpaceTimingStruct=const_cast<FsmcNandTiming *>(&timing);
        FSMC_AttributeSpaceTimingStruct=const_cast<FsmcNandTiming *>(&timing);

        FSMC_NANDInit(this);

        // enable it

        FSMC_NANDCmd(bank,ENABLE);
    }


    /**
     * Destructor. De-init the FSMC.
     */

    FsmcNand::~FsmcNand() {
        FSMC_NANDCmd(_bank,DISABLE);
        FSMC_NANDDeInit(_bank);
    }
}
