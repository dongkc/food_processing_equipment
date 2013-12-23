/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "display/touch/TouchScreenCalibration.h"


namespace stm32plus {
    namespace display {


        /**
         * @brief Three point touch screen calibration, based on the paper "Calibration in touch-screen systems"
         * by Texas Instruments.
         */

        class ThreePointTouchScreenCalibration : public TouchScreenCalibration {

            protected:
                double _ax,_bx,_dx;
                double _ay,_by,_dy;

            public:

                ThreePointTouchScreenCalibration();
                ThreePointTouchScreenCalibration(
                        const Point& p1Panel,const Point& p2Panel,const Point& p3Panel,
                        const Point& p1Touch,const Point& p2Touch,const Point& p3Touch);

                virtual ~ThreePointTouchScreenCalibration() {
                }

                // overrides from TouchScreenCalibration

                virtual Point translate(const Point& rawPoint);
                virtual bool serialise(OutputStream& ostream);
                virtual bool deserialise(InputStream& istream);
        };
    }
}
