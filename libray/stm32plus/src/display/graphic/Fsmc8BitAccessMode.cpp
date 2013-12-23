/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "display/graphic/Fsmc8BitAccessMode.h"
#include "gpio/GpioPort.h"
#include "timing/MillisecondTimer.h"


namespace stm32plus {
    namespace display {

        /**
         * Constructor. Initialises the AFIO GPIO pins for the FSMC used to control an 8080 LCD.
         * @param[in] bank The FSMC bank e.g. FSMC_Bank1_NORSRAM1
         * @param[in] timing The timing structure for this LCD panel
         * @param[in] registerAddressLine The address line index used to switch between data and register select. e.g. 16 = A16.
         * @param[in] registerPin The GPIO pin that corresponds to the register line. e.g. PD11 = address line A16. This constructor will initialise the pin.
         * @param[in] resetPin The GPIO pin that corresponds to the TFT reset line.
         */

        Fsmc8BitAccessMode::Fsmc8BitAccessMode(
                uint32_t bank,
                const Fsmc8080LcdTiming& timing,
                uint16_t registerAddressLine,
                Gpio& registerPin,
                Gpio& resetPin)
                    : Fsmc(bank),
                      _resetPin(resetPin) {

            // initialise the register select pin

            registerPin.initialise(GPIO_Speed_50MHz,GPIO_Mode_AF_PP);

            // initialise the addressing, data and control lines

            GpioPort pd(GPIOD),pe(GPIOE);

            pd.initialise(GPIO_Speed_50MHz, // full speed
                    GPIO_Mode_AF_PP,         // FSMC alternate function
                    GPIO_Pin_0 |                 // D2
                            GPIO_Pin_1 |         // D3
                            GPIO_Pin_4 |         // NOE
                            GPIO_Pin_5 |         // NWE
                            GPIO_Pin_14 |     // D0
                            GPIO_Pin_15         // D1
            );

            pe.initialise(GPIO_Speed_50MHz, // full speed
                    GPIO_Mode_AF_PP, // FSMC alternate function
                    GPIO_Pin_7 |                 // D4
                            GPIO_Pin_8 |         // D5
                            GPIO_Pin_9 |         // D6
                            GPIO_Pin_10            // D7
            );

            // initialise how the FSMC will work and then enable it

            FSMC_Bank=bank;
            FSMC_DataAddressMux=FSMC_DataAddressMux_Disable;
            FSMC_MemoryType=FSMC_MemoryType_SRAM;
            FSMC_MemoryDataWidth=FSMC_MemoryDataWidth_8b;
            FSMC_BurstAccessMode=FSMC_BurstAccessMode_Disable;
            FSMC_WaitSignalPolarity=FSMC_WaitSignalPolarity_Low;
            FSMC_WrapMode=FSMC_WrapMode_Disable;
            FSMC_WaitSignalActive=FSMC_WaitSignalActive_BeforeWaitState;
            FSMC_WriteOperation=FSMC_WriteOperation_Enable;
            FSMC_WaitSignal=FSMC_WaitSignal_Disable;
            FSMC_ExtendedMode=FSMC_ExtendedMode_Disable;
            FSMC_WriteBurst=FSMC_WriteBurst_Disable;
            FSMC_ReadWriteTimingStruct=const_cast<Fsmc8080LcdTiming *> (&timing);
            FSMC_WriteTimingStruct=const_cast<Fsmc8080LcdTiming *> (&timing);
            FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;

            // initialise the FSMC and then enable it

            FSMC_NORSRAMInit(this);

            // calculate the data address

            _dataAddress=static_cast<uint8_t *>(_baseAddress)+(1<<registerAddressLine);
            _registerAddress=static_cast<volatile uint8_t *>(_baseAddress);

            enable(true);
        }


        /**
         * enable or disable the peripheral
         */

        void Fsmc8BitAccessMode::enable(bool enable) {
            FSMC_NORSRAMCmd(_bank,enable ? ENABLE : DISABLE);
        }


        /**
         * Hard-reset the panel
         */

        void Fsmc8BitAccessMode::reset() {

            // let the power stabilise

            MillisecondTimer::delay(10);

            // reset sequence

            _resetPin.set();
            MillisecondTimer::delay(5);
            _resetPin.reset();
            MillisecondTimer::delay(50);
            _resetPin.set();
            MillisecondTimer::delay(50);
        }
    }
}
