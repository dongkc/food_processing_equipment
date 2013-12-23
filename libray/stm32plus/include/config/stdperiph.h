/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#pragma once


/**
 * Setup macros based on the processor you are using and include
 * the common headers from the std peripheral library
 */

#ifdef STM32F10X_HD

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_sdio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_fsmc.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_i2c.h"

#else

#error "Only STM32F10X_HD is currently supported"

#endif

