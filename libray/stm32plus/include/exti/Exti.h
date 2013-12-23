/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "exti/ExtiBase.h"
#include "gpio/Gpio.h"
#include "nvic/Nvic.h"


namespace stm32plus {

    /**
     * @brief Template implementation for the EXTI lines.
     * @tparam Index The index (0..15) of the EXTI line.
     * @tparam Line The EXTI line e.g. EXTI_Line0
     * @tparam Irq The corresponding IRQ for the EXTI line.
     *
     * Exti 0..15 configuration differs only slightly so we define as a template with integral
     * parameters and then declare typedefs for the user usage.
     */

    template<uint8_t Index,uint32_t Line,uint8_t Irq>
    class Exti : public ExtiBase {

        public:

    /**
     * Constructor
     *
     * @param[in] mode_ EXTI_Mode_Event or EXTI_Mode_Interrupt
     * @param[in] trigger_ EXTI_Trigger_Falling / EXTI_Trigger_Rising / EXTI_Trigger_Rising_Falling
     * @param[in] pin_ The GPIO pin to use.
     * @param[in] peripheralIndex_ The line (0..15) This parameter should not be changed from the default supplied by the typedef.
     * @param[in] line_ The EXTI line. This parameter should not be changed from the default supplied by the typedef.
     * @param[in] irq_ The IRQ constant. This parameter should not be changed from the default supplied by the typedef.
     */

        Exti(EXTIMode_TypeDef mode_,
                 EXTITrigger_TypeDef trigger_,
                 const Gpio& pin_,
                 uint8_t peripheralIndex_=Index,
                 uint32_t line_=Line,
                 uint8_t irq_=Irq) : ExtiBase(line_) {

            // save instance ref

            _extiInstances[peripheralIndex_]=this;

            // enable interrupts if we are using them

            if(mode_ == EXTI_Mode_Interrupt)
                Nvic::configureIrq(irq_);

            // configure appropriate GPIO

            pin_.enableExti();

            // initialise the peripheral

            ExtiBase::initialisePeripheral(mode_,trigger_);
        }
    };


    typedef Exti<0,EXTI_Line0,EXTI0_IRQn> Exti0;                                ///< EXTI line 0
    typedef Exti<1,EXTI_Line1,EXTI1_IRQn> Exti1;                                ///< EXTI line 1
    typedef Exti<2,EXTI_Line2,EXTI2_IRQn> Exti2;                                ///< EXTI line 2
    typedef Exti<3,EXTI_Line3,EXTI3_IRQn> Exti3;                                ///< EXTI line 3
    typedef Exti<4,EXTI_Line4,EXTI4_IRQn> Exti4;                                ///< EXTI line 4

    typedef Exti<5,EXTI_Line5,EXTI9_5_IRQn> Exti5;                            ///< EXTI line 5
    typedef Exti<6,EXTI_Line6,EXTI9_5_IRQn> Exti6;                            ///< EXTI line 6
    typedef Exti<7,EXTI_Line7,EXTI9_5_IRQn> Exti7;                            ///< EXTI line 7
    typedef Exti<8,EXTI_Line8,EXTI9_5_IRQn> Exti8;                            ///< EXTI line 8
    typedef Exti<9,EXTI_Line9,EXTI9_5_IRQn> Exti9;                            ///< EXTI line 9

    typedef Exti<10,EXTI_Line10,EXTI15_10_IRQn> Exti10;                    ///< EXTI line 10
    typedef Exti<11,EXTI_Line11,EXTI15_10_IRQn> Exti11;                    ///< EXTI line 11
    typedef Exti<12,EXTI_Line12,EXTI15_10_IRQn> Exti12;                    ///< EXTI line 12
    typedef Exti<13,EXTI_Line13,EXTI15_10_IRQn> Exti13;                    ///< EXTI line 13
    typedef Exti<14,EXTI_Line14,EXTI15_10_IRQn> Exti14;                    ///< EXTI line 14
    typedef Exti<15,EXTI_Line15,EXTI15_10_IRQn> Exti15;                    ///< EXTI line 15
}
