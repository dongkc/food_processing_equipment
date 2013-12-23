/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "config/stdperiph.h"
#include "gpio/Gpio.h"

namespace stm32plus {

    /**
     * @brief Class representing a GPIO port.
     *
     * Acts as a factory for Gpio objects representing each pin as well as
     * providing bulk set, reset and initialise operations.
     */

    class GpioPort {
        protected:
            Gpio _pins[16];
            GPIO_TypeDef *_port;

        protected:
            uint32_t getPeripheral() const;

        public:
            GpioPort(GPIO_TypeDef* port);

            void initialise(GPIOSpeed_TypeDef speed,GPIOMode_TypeDef mode,uint16_t pinIds);
            void set(uint16_t pinIds) const;
            void reset(uint16_t pinIds) const;
            void write(uint16_t value) const;

            Gpio& operator[](int index);
    };

}
