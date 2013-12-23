/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "display/graphic/GraphicTerminalBase.h"


namespace stm32plus {
    namespace display {


        /**
         * Implementation of a terminal for LCDs in portrait mode. In this mode hardware
         * scrolling is supported and will be used when the terminal "goes off the bottom".
         */

        template<class TGraphicsLibrary>
        class GraphicTerminalPortraitImpl : public GraphicTerminalBase<GraphicTerminalPortraitImpl<TGraphicsLibrary>,TGraphicsLibrary> {

            protected:
                uint8_t _smoothScrollStep;
                int16_t _scrollPosition;

            public:
                enum {
                    NO_SMOOTH_SCROLLING = 0,
                    DEFAULT_SMOOTH_SCROLL_STEP = 5
                };

            public:
                GraphicTerminalPortraitImpl(
                        TGraphicsLibrary *gl,
                        const Font *font=NULL,                            // default comes from gl stream selected font
                        bool autoLineFeed=false,
                        uint8_t smoothScrollStep=DEFAULT_SMOOTH_SCROLL_STEP);

                virtual ~GraphicTerminalPortraitImpl() {}

                void reset();
                void scroll();
        };


        /**
         * Constructor
         */

        template<class TGraphicsLibrary>
        GraphicTerminalPortraitImpl<TGraphicsLibrary>::GraphicTerminalPortraitImpl(
                                                                                                                                    TGraphicsLibrary *gl,
                                                                                                                                    const Font *font,
                                                                                                                                    bool autoLineFeed,
                                                                                                                                    uint8_t smoothScrollStep)
            : GraphicTerminalBase<GraphicTerminalPortraitImpl<TGraphicsLibrary>,TGraphicsLibrary>(gl,font,autoLineFeed),
                _smoothScrollStep(smoothScrollStep),
                _scrollPosition(0) {
        }


        /**
         * Scroll the display by one line
         */

        template<class TGraphicsLibrary>
        void GraphicTerminalPortraitImpl<TGraphicsLibrary>::scroll() {

            int i;
            Rectangle rc;
            int16_t screenHeight;

            screenHeight=this->_gl->getHeight();

            rc.Width=this->_gl->getWidth();
            rc.X=0;

            // smooth scroll

            rc.Height=1;

            for(i=0;i<this->_fontSize.Height;i++) {

                _scrollPosition++;

                if(_scrollPosition==screenHeight)
                    _scrollPosition=0;

                this->_gl->setScrollPosition(_scrollPosition);

                rc.Y=_scrollPosition-1;
                this->_gl->clearRectangle(rc);

                MillisecondTimer::delay(_smoothScrollStep);
            }

            // don't allow the cursor to run away and overflow

            if(this->_cursor.Y==this->_terminalSize.Height*2)
                this->_cursor.Y=this->_terminalSize.Height;
        }


        /**
         * Reset after clear
         */

        template<class TGraphicsLibrary>
        void GraphicTerminalPortraitImpl<TGraphicsLibrary>::reset() {

            _scrollPosition=0;
            this->_gl->setScrollPosition(0);
        }
    }

}
