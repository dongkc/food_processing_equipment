/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "fsmc/FsmcSram.h"
#include "fsmc/FsmcSramTiming.h"
#include "gpio/GpioPort.h"


namespace stm32plus {

    /// FSMC address lines on port G
    static const uint16_t pgmap[16]= {
        GPIO_Pin_0,
        GPIO_Pin_0 | GPIO_Pin_1,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_13,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_13 | GPIO_Pin_14
    };

    /// FSMC address lines on port F
    static const uint16_t pfmap[10]= {
        GPIO_Pin_0,
        GPIO_Pin_0 | GPIO_Pin_1,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14,
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15
    };

    /// FSMC address lines on port E
    static const uint16_t pemap[7]= {
    GPIO_Pin_3,
    GPIO_Pin_3 | GPIO_Pin_4,
    GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5,
    GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6,
    GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_2,
    GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_2,
    GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_2
    };

    /// FSMC address lines on port D
    static const uint16_t pdmap[3]={
    GPIO_Pin_11,
    GPIO_Pin_11 | GPIO_Pin_12,
    GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13
    };


    /**
     * Constructor. Initialises the AFIO GPIO pins for the FSMC.
     * @param[in] bank The FSMC bank e.g. FSMC_Bank1_NORSRAM1
     * @param[in] timing The timing structure for this SRAM memory.
     * @param[in] lastAddressLineIndex The last address line needed to fully address this memory. e.g. 18 = A18 = (2**19) 16-bit words
     */

    FsmcSram::FsmcSram(uint32_t bank,const FsmcSramTiming& timing,uint32_t lastAddressLineIndex) : Fsmc(bank) {

        GpioPort pd(GPIOD),pe(GPIOE),pf(GPIOF),pg(GPIOG);

        // A10 is the first line to appear on port G

        if(lastAddressLineIndex>=10)
            pg.initialise(GPIO_Speed_50MHz,GPIO_Mode_AF_PP,pgmap[lastAddressLineIndex-10]);

        // A0..A9 are on port F

        pf.initialise(GPIO_Speed_50MHz,GPIO_Mode_AF_PP,pfmap[lastAddressLineIndex>9 ? 9 : lastAddressLineIndex]);

        // A19..A23 are on port E

        if(lastAddressLineIndex>=19)
            pe.initialise(GPIO_Speed_50MHz,GPIO_Mode_AF_PP,pemap[lastAddressLineIndex-19]);

        // A16..A18 are on port D

        if(lastAddressLineIndex>=16)
            pd.initialise(GPIO_Speed_50MHz,GPIO_Mode_AF_PP,pdmap[(lastAddressLineIndex>18 ? 18 : lastAddressLineIndex)-16]);

        // data and control lines

        pd.initialise(GPIO_Speed_50MHz, // full speed
                GPIO_Mode_AF_PP,         // FSMC alternate function
                        GPIO_Pin_0 |         // D2
                        GPIO_Pin_1 |         // D3
                        GPIO_Pin_4 |         // NOE
                        GPIO_Pin_5 |         // NWE
                        GPIO_Pin_8 |         // D13
                        GPIO_Pin_9 |         // D14
                        GPIO_Pin_10 |     // D15
                        GPIO_Pin_14 |     // D0
                        GPIO_Pin_15         // D1
        );

        pe.initialise(GPIO_Speed_50MHz, // full speed
                GPIO_Mode_AF_PP,         // FSMC alternate function
                        GPIO_Pin_0 |         // NBL0
                        GPIO_Pin_1 |         // NBL1
                        GPIO_Pin_7 |         // D4
                        GPIO_Pin_8 |         // D5
                        GPIO_Pin_9 |         // D6
                        GPIO_Pin_10 |     // D7
                        GPIO_Pin_11 |     // D8
                        GPIO_Pin_12 |     // D9
                        GPIO_Pin_13 |     // D10
                        GPIO_Pin_14 |     // D11
                        GPIO_Pin_15         // D12
        );

        // initialise how the FSMC will work and then enable it

        FSMC_Bank=bank;
        FSMC_DataAddressMux=FSMC_DataAddressMux_Disable;
        FSMC_MemoryType=FSMC_MemoryType_SRAM;
        FSMC_MemoryDataWidth=FSMC_MemoryDataWidth_16b;
        FSMC_BurstAccessMode=FSMC_BurstAccessMode_Disable;
        FSMC_WaitSignalPolarity=FSMC_WaitSignalPolarity_Low;
        FSMC_WrapMode=FSMC_WrapMode_Disable;
        FSMC_WaitSignalActive=FSMC_WaitSignalActive_BeforeWaitState;
        FSMC_WriteOperation=FSMC_WriteOperation_Enable;
        FSMC_WaitSignal=FSMC_WaitSignal_Disable;
        FSMC_ExtendedMode=FSMC_ExtendedMode_Disable;
        FSMC_WriteBurst=FSMC_WriteBurst_Disable;
        FSMC_ReadWriteTimingStruct=const_cast<FsmcSramTiming *> (&timing);
        FSMC_WriteTimingStruct=const_cast<FsmcSramTiming *> (&timing);
        FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;

        // initialise the FSMC and then enable it

        FSMC_NORSRAMInit(this);
        FSMC_NORSRAMCmd(bank,ENABLE);
    }

    /**
     * Destructor. De-init the FSMC.
     */

    FsmcSram::~FsmcSram() {
        FSMC_NORSRAMCmd(_bank,DISABLE);
        FSMC_NORSRAMDeInit(_bank);
    }
}
