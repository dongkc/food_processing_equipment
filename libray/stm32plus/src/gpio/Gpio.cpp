/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "gpio/Gpio.h"


namespace stm32plus {

    /**
     * Set the port for this pin.
     * @param[in] port The port structure.
     */

    void Gpio::setPort(GPIO_TypeDef* port) {
        _port=port;
    }

    /**
     * Set the pin.
     * @param[in] pin The pin in library format, e.g. GPIO_Pin_0
     */

    void Gpio::setPin(uint16_t pin) {
        _pin=pin;
    }

    /**
     * Initialise the pin.
     * @param[in] speed The speed of the pin.
     * @param[in] mode The pin mode.
     */

    void Gpio::initialise(GPIOSpeed_TypeDef speed,GPIOMode_TypeDef mode) const {

        GPIO_InitTypeDef initStruct;

        initStruct.GPIO_Pin=_pin;
        initStruct.GPIO_Speed=speed;
        initStruct.GPIO_Mode=mode;

        GPIO_Init(_port,&initStruct);
    }

    /**
     * Set the pin to HIGH.
     */

    void Gpio::set() const {
        GPIO_WriteBit(_port,_pin,Bit_SET);
    }

    /**
     * Set the pin to LOW.
     */

    void Gpio::reset() const {
        GPIO_WriteBit(_port,_pin,Bit_RESET);
    }

    /**
     * Allow setting/resetting from a variable.
     * @param[in] state The new state of the pin.
     */

    void Gpio::setState(bool state) const {
        GPIO_WriteBit(_port,_pin,state ? Bit_SET : Bit_RESET);
    }

    /**
     * Read a pin state.
     * @return The pin state.
     */

    bool Gpio::read() const {
        return GPIO_ReadInputDataBit(_port,_pin);
    }


    /**
     * Enable EXTI for this port/pin
     */

    void Gpio::enableExti() const {

        uint8_t portSource,pinSource;

        // AFIO needs to be on

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

        initialise(GPIO_Speed_50MHz,GPIO_Mode_IN_FLOATING);
        getPortAndPinSource(portSource,pinSource);
        GPIO_EXTILineConfig(portSource,pinSource);
    }


    /**
     * Get the port and pin source for EXTI
     * @param[out] portSource The port source
     * @param[out] pinSource The pin source
     */

    void Gpio::getPortAndPinSource(uint8_t& portSource,uint8_t& pinSource) const {

        switch(reinterpret_cast<uint32_t>(_port)) {
            case GPIOA_BASE: portSource=GPIO_PortSourceGPIOA; break;
            case GPIOB_BASE: portSource=GPIO_PortSourceGPIOB; break;
            case GPIOC_BASE: portSource=GPIO_PortSourceGPIOC; break;
            case GPIOD_BASE: portSource=GPIO_PortSourceGPIOD; break;
            case GPIOE_BASE: portSource=GPIO_PortSourceGPIOE; break;
            case GPIOF_BASE: portSource=GPIO_PortSourceGPIOF; break;
            case GPIOG_BASE: portSource=GPIO_PortSourceGPIOG; break;
            default: portSource=0; break;
        }

        switch(_pin) {
            case GPIO_Pin_0: pinSource=GPIO_PinSource0; break;
            case GPIO_Pin_1: pinSource=GPIO_PinSource1; break;
            case GPIO_Pin_2: pinSource=GPIO_PinSource2; break;
            case GPIO_Pin_3: pinSource=GPIO_PinSource3; break;
            case GPIO_Pin_4: pinSource=GPIO_PinSource4; break;
            case GPIO_Pin_5: pinSource=GPIO_PinSource5; break;
            case GPIO_Pin_6: pinSource=GPIO_PinSource6; break;
            case GPIO_Pin_7: pinSource=GPIO_PinSource7; break;
            case GPIO_Pin_8: pinSource=GPIO_PinSource8; break;
            case GPIO_Pin_9: pinSource=GPIO_PinSource9; break;
            case GPIO_Pin_10: pinSource=GPIO_PinSource10; break;
            case GPIO_Pin_11: pinSource=GPIO_PinSource11; break;
            case GPIO_Pin_12: pinSource=GPIO_PinSource12; break;
            case GPIO_Pin_13: pinSource=GPIO_PinSource13; break;
            case GPIO_Pin_14: pinSource=GPIO_PinSource14; break;
            case GPIO_Pin_15: pinSource=GPIO_PinSource15; break;
            default: pinSource=0; break;
        }
    }
}
