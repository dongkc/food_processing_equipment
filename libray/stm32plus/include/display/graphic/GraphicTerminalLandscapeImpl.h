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
         * Implementation of a terminal for LCDs in landscape mode. In this mode hardware
         * scrolling is not supported and the terminal will clear down and go back to the
         * top when the bottom is reached.
         */

        template<class TGraphicsLibrary>
        class GraphicTerminalLandscapeImpl : public GraphicTerminalBase<GraphicTerminalLandscapeImpl<TGraphicsLibrary>,TGraphicsLibrary> {

            public:
                GraphicTerminalLandscapeImpl(
                        TGraphicsLibrary *gl,
                        const Font *font=NULL,                            // default comes from gl stream selected font
                        bool autoLineFeed=false
                        );

                virtual ~GraphicTerminalLandscapeImpl() {}

                void reset();
                void scroll();
        };


        /**
         * Constructor
         */

        template<class TGraphicsLibrary>
        GraphicTerminalLandscapeImpl<TGraphicsLibrary>::GraphicTerminalLandscapeImpl(
                        TGraphicsLibrary *gl,
                        const Font *font,
                        bool autoLineFeed)
            : GraphicTerminalBase<GraphicTerminalLandscapeImpl<TGraphicsLibrary>,TGraphicsLibrary>(gl,font,autoLineFeed) {
        }


        /**
         * Scroll the display by one line
         */

        template<class TGraphicsLibrary>
        void GraphicTerminalLandscapeImpl<TGraphicsLibrary>::scroll() {
            this->clearScreen();
        }


        /**
         * Reset after clear
         */

        template<class TGraphicsLibrary>
        void GraphicTerminalLandscapeImpl<TGraphicsLibrary>::reset() {
            // no addition requirements
        }
    }
}
