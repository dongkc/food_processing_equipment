/*
 ******************************* C SOURCE FILE *******************************
 **                                                                         **
 ** interrupt.cpp - 
 **                                                                         **
 ** 11/12/2013 05:49:36 PM                                                  **
 **                                                                         **
 ** Copyright (c) 2010, Kechang Dong                                        **
 ** All rights reserved.                                                    **
 **                                                                         **
 *****************************************************************************
 */
#define __INTERRUPT_SRC__
/****************************************************************************/
/**                             MODULES USED                               **/
/****************************************************************************/
#include <stdint.h>

/****************************************************************************/
/**                         DEFINITIONS AND MACROS                         **/
/****************************************************************************/
extern "C" {
    extern volatile uint32_t _counter;
}

extern uint32_t g_swb_delay;

namespace Zebra {

extern uint8_t g_interrupt_period_us;
extern uint8_t g_group_a_delay;
extern uint8_t g_group_b_delay;

extern bool g_input_flag[6];
extern bool g_input_need_reset[6];

extern bool g_swb_switch_on;
extern bool g_swb_need_set;
extern bool g_swb_flag;

static uint64_t swb_counter = 0;
extern "C" void SysTick_Handler(void) {
    //stm32plus timer need this
    _counter++;

static uint32_t counter[6] = { 0, 0, 0, 0, 0, 0};

    for (uint8_t i = 0; i < 3; ++i) {
        if (g_input_flag[i] == true) {
            counter[i]++;
            if (counter[i] >= g_group_a_delay) {
                g_input_need_reset[i] = true;
                counter[i] = 0;
            }
        }
    }

    if (g_swb_flag == true) {
        swb_counter++;
        //if (swb_counter >= (30000000 / 4095) * (g_swb_delay /  g_interrupt_period_us)) {
        if (swb_counter >= (7326 * g_swb_delay) /  g_interrupt_period_us) {
            g_swb_need_set = true;
            swb_counter = 0;
        }
    }

    if (g_swb_switch_on == true) {
        for (uint8_t i = 3; i < 6; ++i) {
            if (g_input_flag[i] == true) {
                counter[i]++;
                if (counter[i] >= g_group_b_delay) {
                    g_input_need_reset[i] = true;
                    counter[i] = 0;
                }
            }
        }
    }


}

}
/****************************************************************************/
/**                                  EOF                                   **/
/****************************************************************************/
