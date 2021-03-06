/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "display/touch/TouchScreen.h"
#include "observer/Observer.h"
#include "observer/ObserverLinkManager.h"
#include "exti/ExtiBase.h"
#include "spi/SpiPollingWriter.h"
#include "gpio/Gpio.h"


namespace stm32plus {
    namespace display {

        /**
         * @brief ADS7843TouchScreen supporting async notifications via an EXTI line
         *
         * There can be only one instance of this class in scope at a time. The ADS7843 is a classic resistive
         * 4-wire ADC supporting an SPI interface.
         */

        class ADS7843AsyncTouchScreen :    public TouchScreen,
                                                                        public Observer {

            protected:
                SpiPollingWriter& _spiWriter;
                const Gpio& _irqPin;
                ObserverLinkManager _linkManager;

                enum ControlBits {
                    START = 0x80,
                    A2    = 0x40,
                  A1    = 0x20,
                  A0    = 0x10,
                  MODE1 = 0x8,
                  MODE0 = 0x4,
                  PD1   = 0x2,
                  PD0   = 0x1,

                  // channels from the above combinations

                  ChannelX =  A0,
                    ChannelY =  A2 | A0
                };


            protected:
                void getSamples(uint16_t *xvalues,uint16_t *yvalues,uint16_t sampleCount) const;
                void getSamples(uint8_t firstCommand,uint8_t lastCommand,uint16_t *values,uint16_t sampleCount) const;
                uint16_t fastMedian(uint16_t *samples) const;

            public:
                ADS7843AsyncTouchScreen(
                        TouchScreenCalibration& calibration,
                        TouchScreenPostProcessor& postProcessor,
                        SpiPollingWriter& spi,
                        const Gpio& irqPin,
                        ExtiBase& exti);

                virtual ~ADS7843AsyncTouchScreen() {}

                /**
                 * Return true if the screen is touched. i.e. PENIRQ = low
                 * @return true if touched.
                 */

                bool isTouched() const {
                    return !_irqPin.read();
                }

                // overrides from TouchScreen
                virtual bool getCoordinates(Point& point);

                // overrides from Observer
                virtual void onNotify(Observable& sender,ObservableEvent::E event,void *context);
                virtual void onSubjectDestroyed();
        };
    }
}

