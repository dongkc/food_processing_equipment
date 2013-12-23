/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "config/stdperiph.h"
#include "observer/Observable.h"

namespace stm32plus {

/**
 * @brief EXTI base class
 */

    class ExtiBase : public Observable {

        protected:
            uint32_t _line;

        protected:
            void initialisePeripheral(EXTIMode_TypeDef mode_,EXTITrigger_TypeDef trigger_);

            /**
             * Constructor
             * @param[in] line_ The EXTI line (e.g. EXTI_Line0)
             */

            ExtiBase(uint32_t line_) {
                _line=line_;
            }

        public:
            /// Addresses of the 16 EXTI instances
            static ExtiBase *_extiInstances[16];

            /**
             * Generate a software interrupt on this line
             */

            void generateSoftwareInterrupt() const {
                EXTI_GenerateSWInterrupt(_line);
            }

            /**
             * Test if this line is set or not
             * @return true if it is set
             */

            bool isSet() const {
                return EXTI_GetFlagStatus(_line) == SET;
            }
    };
}
