/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "config/stdperiph.h"

namespace stm32plus {

    /**
     * @brief Class for GPIO pin functionality.
     *
     * This exposes the common operations that you might want to do to a GPIO pin. This class is not
     * usually directly constructed. Instead it should be optained from an instance of GpioPort.
     *
     * This class is designed to be safe to do a bitwise copy.
     */

    class Gpio {

        protected:
            GPIO_TypeDef *_port;
            uint16_t _pin;

        protected:
            void getPortAndPinSource(uint8_t& portSource,uint8_t& pinSource) const;

        public:
            void setPort(GPIO_TypeDef* port);
            void setPin(uint16_t pin);

            void initialise(GPIOSpeed_TypeDef speed,GPIOMode_TypeDef mode) const;
            void set() const;
            void reset() const;
            void setState(bool state) const;
            bool read() const;
            void enableExti() const;
    };
}

