/*
 ******************************* C HEADER FILE *******************************
 **                                                                         **
 ** dev-mgr.h - 
 **                                                                         **
 ** 03/15/2013 05:17:51 AM                                                  **
 **                                                                         **
 ** Copyright (c) 2011, Kechang Dong                                        **
 ** All rights reserved.                                                    **
 **                                                                         **
 *****************************************************************************
 */
#ifndef __DEV_MGR_HEADER__
#define __DEV_MGR_HEADER__
/****************************************************************************/
/**                              MODULES USED                              **/
/****************************************************************************/
#include "gpio/GpioPort.h"

namespace Zebra {
/****************************************************************************/
/**                         DEFINITIONS AND MACROS                         **/
/****************************************************************************/

/****************************************************************************/
/**                         TYPEDEFS AND STRUCTURES                        **/
/****************************************************************************/
typedef enum {
    DIP_A_0  = 2000,
    DIP_A_1  = 1700,
    DIP_A_2  = 1400,
    DIP_A_3  = 1100,
    DIP_A_4  = 3250,
    DIP_A_5  = 2950,
    DIP_A_6  = 2650,
    DIP_A_7  = 2350,
    DIP_A_8  = 4500,
    DIP_A_9  = 4200,
    DIP_A_10 = 3900,
    DIP_A_11 = 3600,
    DIP_B_0  = 2000,
    DIP_B_1  = 2500,
    DIP_B_2  = 3000,
    DIP_B_3  = 3500,
    DIP_B_4  = 4000
} dip_value_t;

class DevMgr {
public:
    DevMgr();
    void init();
    uint8_t readDipA();
    uint8_t readDipB();

    ~DevMgr();

public:
    stm32plus::Gpio* digital_input[6];
    stm32plus::Gpio* digital_output[6];

    stm32plus::Gpio* sw_a;
    stm32plus::Gpio* sw_b;

    stm32plus::Gpio* dip_a_0;
    stm32plus::Gpio* dip_a_1;
    stm32plus::Gpio* dip_a_2;
    stm32plus::Gpio* dip_a_3;

    stm32plus::Gpio* dip_b_0;
    stm32plus::Gpio* dip_b_1;
    stm32plus::Gpio* dip_b_2;
    stm32plus::Gpio* dip_b_3;

private:
    stm32plus::GpioPort pa;
    stm32plus::GpioPort pb;
    stm32plus::GpioPort pc;

};

/****************************************************************************/
/**                           EXPORTED VARIABLES                           **/
/****************************************************************************/
#ifndef __DEV_MGR_SRC__
extern DevMgr* const g_dev_mgr;
#endif
/****************************************************************************/
/**                           EXPORTED FUNCTIONS                           **/
/****************************************************************************/

}
#endif
/****************************************************************************/
/**                                  EOF                                   **/
/****************************************************************************/
