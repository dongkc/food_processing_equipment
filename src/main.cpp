#include <stdio.h>
#include "dev-mgr.h"
#include "nvic/Nvic.h"
#include "timing/MillisecondTimer.h"
#include "usart/Usart1.h"
#include "usart/UsartPollingWriter.h"

extern "C" {
    #include "stm32f10x_iwdg.h"
}
extern uint32_t g_swb_delay;

using namespace stm32plus;

namespace Zebra {

uint8_t g_interrupt_period_us = 25;
uint8_t g_group_a_delay = 0;
uint8_t g_group_b_delay = 0;

bool g_input_flag[6];
bool g_input_need_reset[6];

bool g_swb_flag = false;
bool g_swb_need_set = false;
bool g_swb_switch_on = false;

uint8_t g_swb_value;
uint8_t g_swb_value_last;

uint8_t g_input_value[6];
uint8_t g_input_value_last[6];


extern "C" int main(void) {

    g_dev_mgr->init();

    uint16_t table_a[12] = {DIP_A_0,
                            DIP_A_1,
                            DIP_A_2,
                            DIP_A_3,
                            DIP_A_4,
                            DIP_A_5,
                            DIP_A_6,
                            DIP_A_7,
                            DIP_A_8,
                            DIP_A_9,
                            DIP_A_10,
                            DIP_A_11};
    uint16_t table_b[5] = {DIP_B_0,
                           DIP_B_1,
                           DIP_B_2,
                           DIP_B_3,
                           DIP_B_4};

    uint8_t index = g_dev_mgr->readDipA();
    if (index > 11) {
        index = 0;
    }
    g_group_a_delay = table_a[index] / g_interrupt_period_us;

    index = g_dev_mgr->readDipB();
    if (index > 4) {
        index = 0;
    }
    g_group_b_delay = table_b[index] / g_interrupt_period_us;

    Nvic::initialise();
    MillisecondTimer::initialise();

    Usart1 usart(9600);
    while (1) {

#if 0
        static uint32_t tmp = 0;
        if (tmp++ > 65535) {
            printf("DELAY = %d, %d\r\n", g_swb_delay, 7326 * g_swb_delay /  g_interrupt_period_us);
            tmp = 0;
        }
#endif

        if (g_dev_mgr->sw_a->read() != 0) {
            for (uint8_t i = 0; i < 3; ++i) {
                g_input_value[i] = g_dev_mgr->digital_input[i]->read();
                if (g_input_value[i] == true && g_input_value_last[i] == false) {
                    g_input_flag[i] = true;

                    g_dev_mgr->digital_output[i]->reset();

                }

                if (g_input_need_reset[i] == true) {
                    g_dev_mgr->digital_output[i]->set();

                    g_input_flag[i] = false;
                    g_input_need_reset[i] = false;
                }

                g_input_value_last[i] = g_input_value[i];
            }
        }


        g_swb_value = g_dev_mgr->sw_b->read();
        if (g_swb_value == false) {
            g_swb_switch_on = false;
        } else if (g_swb_value == true && g_swb_value_last == false) {
            g_swb_flag = true;
        }

        if (g_swb_need_set == true) {
            if (g_swb_value == true) {
                g_swb_switch_on = true;
            }

            g_swb_flag = false;
            g_swb_need_set = false;
        }

        g_swb_value_last = g_swb_value;


        if (g_swb_switch_on == true) {
            for (uint8_t i = 3; i < 6; ++i) {
                g_input_value[i] = g_dev_mgr->digital_input[i]->read();
                if (g_input_value[i] == false) {
                    g_dev_mgr->digital_output[i]->set();
                } else if (g_input_value[i] == true && g_input_value_last[i] == false) {
                    g_input_flag[i] = true;
                }

                if (g_input_need_reset[i] == true) {
                    if (g_input_value[i] == true) {
                        g_dev_mgr->digital_output[i]->reset();
                    }

                    g_input_flag[i] = false;
                    g_input_need_reset[i] = false;
                }

                g_input_value_last[i] = g_input_value[i];
            }
        }

        //IWDG_ReloadCounter();
    }
}

}  // namespace Zebra
