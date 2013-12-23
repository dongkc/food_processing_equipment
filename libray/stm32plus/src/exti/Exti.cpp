/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "exti/Exti.h"
#include "config/interrupts.h"


namespace stm32plus {

    ExtiBase *ExtiBase::_extiInstances[16];


    /**
     * Initialise the EXTI peripheral.
     *
     * @param[in] mode_ EXTI_Mode_Event or EXTI_Mode_Interrupt
     * @param[in] trigger_ EXTI_Trigger_Falling / EXTI_Trigger_Rising / EXTI_Trigger_Rising_Falling
     */

    void ExtiBase::initialisePeripheral(EXTIMode_TypeDef mode_,EXTITrigger_TypeDef trigger_) {

        EXTI_InitTypeDef init;

        init.EXTI_Line=_line;
        init.EXTI_Mode=mode_;
        init.EXTI_Trigger=trigger_;
        init.EXTI_LineCmd=ENABLE;

        EXTI_Init(&init);
    }
}


using namespace stm32plus;

extern "C" {

#if defined(USE_EXTI0_INTERRUPT) || \
        defined(USE_EXTI1_INTERRUPT) || \
        defined(USE_EXTI2_INTERRUPT) || \
        defined(USE_EXTI3_INTERRUPT) || \
        defined(USE_EXTI4_INTERRUPT) || \
        defined(USE_EXTI9_5_INTERRUPT) || \
        defined(USE_EXTI15_10_INTERRUPT)

        static void Exti_InterruptHandler(uint32_t line_,uint8_t peripheralIndex_) {

            if(EXTI_GetITStatus(line_)!=RESET) {
                ExtiBase::_extiInstances[peripheralIndex_]->notifyObservers(ObservableEvent::EXTI_Triggered);
                EXTI_ClearITPendingBit(line_);
            }
        }

#endif
#if defined(USE_EXTI0_INTERRUPT)

    void EXTI0_IRQHandler(void) {
        Exti_InterruptHandler(EXTI_Line0,0);
    }

#endif
#if defined(USE_EXTI1_INTERRUPT)

    void EXTI1_IRQHandler(void) {
        Exti_InterruptHandler(EXTI_Line1,1);
    }

#endif
#if defined(USE_EXTI2_INTERRUPT)

    void EXTI2_IRQHandler(void) {
        Exti_InterruptHandler(EXTI_Line2,2);
    }

#endif
#if defined(USE_EXTI3_INTERRUPT)

    void EXTI3_IRQHandler(void) {
        Exti_InterruptHandler(EXTI_Line3,3);
    }

#endif
#if defined(USE_EXTI4_INTERRUPT)

    void EXTI4_IRQHandler(void) {
        Exti_InterruptHandler(EXTI_Line4,4);
    }

#endif
#if defined(USE_EXTI9_5_INTERRUPT)

    void EXTI9_5_IRQHandler(void) {
        Exti_InterruptHandler(EXTI_Line5,5);
        Exti_InterruptHandler(EXTI_Line6,6);
        Exti_InterruptHandler(EXTI_Line7,7);
        Exti_InterruptHandler(EXTI_Line8,8);
        Exti_InterruptHandler(EXTI_Line9,9);
    }

#endif
#if defined(USE_EXTI15_10_INTERRUPT)

    void EXTI15_10_IRQHandler(void) {

        Exti_InterruptHandler(EXTI_Line10,10);
        Exti_InterruptHandler(EXTI_Line11,11);
        Exti_InterruptHandler(EXTI_Line12,12);
        Exti_InterruptHandler(EXTI_Line13,13);
        Exti_InterruptHandler(EXTI_Line14,14);
        Exti_InterruptHandler(EXTI_Line15,15);
    }

#endif

} // extern "C"
