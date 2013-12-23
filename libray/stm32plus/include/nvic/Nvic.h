/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "config/stdperiph.h"
#include "misc.h"
#include <cstring>

namespace stm32plus {

    /**
     * @brief Nvic manager. This is a singleton that can be referenced from anywhere.
     *
     * The NVIC manager abstracts configuration of the NVIC away from the user.
     */

    class Nvic {

        public:

            /**
             * Initialise the Nvic. We set all bits for the pre-emption priority
             */

            static void initialise() {
                // 4 bits for pre-emption, 0 bits for sub
                NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
            }

            /**
             * Enable or disable an interrupt.
             * @param[in] interrupt The peripheral identifier.
             * @param[in] state The new state, ENABLE or DISABLE. Default is ENABLE.
             * @param[in] preemptionPriority The new pre-emption priority. Default is 0.
             */

            static void configureIrq(
                    uint8_t interrupt,
                    FunctionalState state=ENABLE,
                    uint8_t preemptionPriority=0) {

                NVIC_InitTypeDef nit;

                nit.NVIC_IRQChannel=interrupt;
                nit.NVIC_IRQChannelPreemptionPriority=preemptionPriority;
                nit.NVIC_IRQChannelSubPriority=0;
                nit.NVIC_IRQChannelCmd=state;

                NVIC_Init(&nit);
            }
    };
}
