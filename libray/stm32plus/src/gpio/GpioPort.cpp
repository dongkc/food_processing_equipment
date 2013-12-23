/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "gpio/GpioPort.h"
#include "config/stdperiph.h"

namespace stm32plus {

    /**
     * Constructor
     * @param[in] port The port that will be controlled, e.g. GPIOA. Enables
     * the clock on the given port.
     */

    GpioPort::GpioPort(GPIO_TypeDef *port) {

        _port=port;

        // enable the port

        RCC_APB2PeriphClockCmd(getPeripheral(),ENABLE);

        // set the port in the pins

        for(int i=0;i < 16;i++) {
            _pins[i].setPort(port);
            _pins[i].setPin(1 << i); // pin id is compatible with the C library calls
        }
    }


    /**
     * Initialise one or more pins.
     * @param[in] speed The speed of the pin.
     * @param[in] mode The pin mode.
     * @param[in] pinIds A bit mask of all the pins to configure.
     */

    void GpioPort::initialise(GPIOSpeed_TypeDef speed,GPIOMode_TypeDef mode,uint16_t pinIds) {

        GPIO_InitTypeDef ginit;

        ginit.GPIO_Pin=pinIds;
        ginit.GPIO_Mode=mode;
        ginit.GPIO_Speed=speed;

        GPIO_Init(_port,&ginit);
    }

    /**
     * Get the peripheral id from the port, e.g. GPIOA=RCC_APB2Periph_GPIOA
     * @return The peripheral clock id or UINT32_MAX if the class is incorrectly configured.
     */

    uint32_t GpioPort::getPeripheral() const {

        if(_port == GPIOA)
            return RCC_APB2Periph_GPIOA;
        else if(_port == GPIOB)
            return RCC_APB2Periph_GPIOB;
        else if(_port == GPIOC)
            return RCC_APB2Periph_GPIOC;
        else if(_port == GPIOD)
            return RCC_APB2Periph_GPIOD;
        else if(_port == GPIOE)
            return RCC_APB2Periph_GPIOE;
        else if(_port == GPIOF)
            return RCC_APB2Periph_GPIOF;
        else if(_port == GPIOG)
            return RCC_APB2Periph_GPIOG;

        return 655251;
    }

    /**
     * Get the pin using the array operator.
     * @param[in] index The pin index (0..15) to return.
     * @return A reference to the Gpio object that represents the pin.
     */

    Gpio& GpioPort::operator[](int index) {
        return _pins[index];
    }

    /**
     * Set some pins to the HIGH state.
     * @param[in] pinIds The bitmask of pin ids to set e.g. GPIO_Pin_11
     */

    void GpioPort::set(uint16_t pinIds) const {
        ::GPIO_SetBits(_port,pinIds);
    }

    /**
     * Set some pins to the LOW state.
     * @param[in] pinIds The bitmask of pin ids to set e.g. GPIO_Pin_11
     */

    void GpioPort::reset(uint16_t pinIds) const {
        ::GPIO_ResetBits(_port,pinIds);
    }

    /**
     * Write a value direct to the port.
     * @param[in] value The value to write to the port.
     */

    void GpioPort::write(uint16_t value) const {
        ::GPIO_Write(_port,value);
    }
}
