/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once


#include "display/graphic/GraphicsLibrary.h"
#include "display/graphic/Fsmc8BitAccessMode.h"
#include "display/graphic/Fsmc16BitAccessMode.h"
#include "display/graphic/tft/ili9325/ILI9325.h"
#include "display/graphic/tft/ili9481/ILI9481.h"
#include "display/graphic/tft/ili9327/ILI9327.h"
#include "display/graphic/tft/ili9327/ILI9327400x240PanelTraits.h"
#include "display/graphic/tft/hx8347a/HX8347A.h"
#include "display/graphic/tft/mc2pa8201/MC2PA8201.h"
#include "display/graphic/GraphicTerminalPortraitImpl.h"
#include "display/graphic/GraphicTerminalLandscapeImpl.h"


/*
 * Useful typedefs to ease the pain of typing out template parameters
 */

namespace stm32plus {
    namespace display {

        /*
         * ILI9325 interface: 64K and 262K colours, portrait and landscape
         */

        typedef GraphicsLibrary<ILI9325<PORTRAIT,COLOURS_16BIT,Fsmc16BitAccessMode>,Fsmc16BitAccessMode> ILI9325_Portrait_64K;
        typedef GraphicsLibrary<ILI9325<LANDSCAPE,COLOURS_16BIT,Fsmc16BitAccessMode>,Fsmc16BitAccessMode> ILI9325_Landscape_64K;

        typedef GraphicsLibrary<ILI9325<PORTRAIT,COLOURS_18BIT,Fsmc16BitAccessMode>,Fsmc16BitAccessMode> ILI9325_Portrait_262K;
        typedef GraphicsLibrary<ILI9325<LANDSCAPE,COLOURS_18BIT,Fsmc16BitAccessMode>,Fsmc16BitAccessMode> ILI9325_Landscape_262K;

        typedef GraphicTerminalPortraitImpl<ILI9325_Portrait_64K> ILI9325_Terminal_Portrait_64K;
        typedef GraphicTerminalLandscapeImpl<ILI9325_Landscape_64K> ILI9325_Terminal_Landscape_64K;

        typedef GraphicTerminalPortraitImpl<ILI9325_Portrait_262K> ILI9325_Terminal_Portrait_262K;
        typedef GraphicTerminalLandscapeImpl<ILI9325_Landscape_262K> ILI9325_Terminal_Landscape_262K;

        /*
         * ILI9481 interface: 64K and 262K colours, portrait and landscape
         */

        typedef GraphicsLibrary<ILI9481<PORTRAIT,COLOURS_16BIT,Fsmc16BitAccessMode>,Fsmc16BitAccessMode> ILI9481_Portrait_64K;
        typedef GraphicsLibrary<ILI9481<LANDSCAPE,COLOURS_16BIT,Fsmc16BitAccessMode>,Fsmc16BitAccessMode> ILI9481_Landscape_64K;

        typedef GraphicsLibrary<ILI9481<PORTRAIT,COLOURS_18BIT,Fsmc16BitAccessMode>,Fsmc16BitAccessMode> ILI9481_Portrait_262K;
        typedef GraphicsLibrary<ILI9481<LANDSCAPE,COLOURS_18BIT,Fsmc16BitAccessMode>,Fsmc16BitAccessMode> ILI9481_Landscape_262K;

        typedef GraphicTerminalPortraitImpl<ILI9481_Portrait_64K> ILI9481_Terminal_Portrait_64K;
        typedef GraphicTerminalLandscapeImpl<ILI9481_Landscape_64K> ILI9481_Terminal_Landscape_64K;

        typedef GraphicTerminalPortraitImpl<ILI9481_Portrait_262K> ILI9481_Terminal_Portrait_262K;
        typedef GraphicTerminalLandscapeImpl<ILI9481_Landscape_262K> ILI9481_Terminal_Landscape_262K;

        /*
         * HX8347A interface: 64K colours, portrait and landscape
         */

        typedef GraphicsLibrary<HX8347A<PORTRAIT,COLOURS_16BIT,Fsmc16BitAccessMode>,Fsmc16BitAccessMode> HX8347A_Portrait_64K;
        typedef GraphicsLibrary<HX8347A<LANDSCAPE,COLOURS_16BIT,Fsmc16BitAccessMode>,Fsmc16BitAccessMode> HX8347A_Landscape_64K;

        typedef GraphicTerminalPortraitImpl<HX8347A_Portrait_64K> HX8347A_Terminal_Portrait_64K;
        typedef GraphicTerminalLandscapeImpl<HX8347A_Landscape_64K> HX8347A_Terminal_Landscape_64K;

        /*
         * Nokia 2730 interface: 64K, 262K, 16M colours, portrait and landscape
         */

        typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_16BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> Nokia2730_Portrait_64K;
        typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_16BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> Nokia2730_Landscape_64K;

        typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_18BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> Nokia2730_Portrait_262K;
        typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_18BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> Nokia2730_Landscape_262K;

        typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_24BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> Nokia2730_Portrait_16M;
        typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_24BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> Nokia2730_Landscape_16M;

        typedef GraphicTerminalPortraitImpl<Nokia2730_Portrait_64K> Nokia2730_Terminal_Portrait_64K;
        typedef GraphicTerminalLandscapeImpl<Nokia2730_Landscape_64K> Nokia2730_Terminal_Landscape_64K;

        typedef GraphicTerminalPortraitImpl<Nokia2730_Portrait_262K> Nokia2730_Terminal_Portrait_262K;
        typedef GraphicTerminalLandscapeImpl<Nokia2730_Landscape_262K> Nokia2730_Terminal_Landscape_262K;

        typedef GraphicTerminalPortraitImpl<Nokia2730_Portrait_16M> Nokia2730_Terminal_Portrait_16M;
        typedef GraphicTerminalLandscapeImpl<Nokia2730_Landscape_16M> Nokia2730_Terminal_Landscape_16M;

        /*
         * Nokia 6300 interface: 64K, 262K, 16M colours, portrait and landscape
         */

        typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_16BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> Nokia6300_Portrait_64K;
        typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_16BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> Nokia6300_Landscape_64K;

        typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_18BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> Nokia6300_Portrait_262K;
        typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_18BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> Nokia6300_Landscape_262K;

        typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_24BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> Nokia6300_Portrait_16M;
        typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_24BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> Nokia6300_Landscape_16M;

        typedef GraphicTerminalPortraitImpl<Nokia6300_Portrait_64K> Nokia6300_Terminal_Portrait_64K;
        typedef GraphicTerminalLandscapeImpl<Nokia6300_Landscape_64K> Nokia6300_Terminal_Landscape_64K;

        typedef GraphicTerminalPortraitImpl<Nokia6300_Portrait_262K> Nokia6300_Terminal_Portrait_262K;
        typedef GraphicTerminalLandscapeImpl<Nokia6300_Landscape_262K> Nokia6300_Terminal_Landscape_262K;

        typedef GraphicTerminalPortraitImpl<Nokia6300_Portrait_16M> Nokia6300_Terminal_Portrait_16M;
        typedef GraphicTerminalLandscapeImpl<Nokia6300_Landscape_16M> Nokia6300_Terminal_Landscape_16M;

        /*
         * Nokia N82 interface: 64K, 262K, 16M colours, portrait and landscape
         */

        typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_16BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> NokiaN82_Portrait_64K;
        typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_16BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> NokiaN82_Landscape_64K;

        typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_18BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> NokiaN82_Portrait_262K;
        typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_18BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> NokiaN82_Landscape_262K;

        typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_24BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> NokiaN82_Portrait_16M;
        typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_24BIT,Fsmc8BitAccessMode>,Fsmc8BitAccessMode> NokiaN82_Landscape_16M;

        typedef GraphicTerminalPortraitImpl<NokiaN82_Portrait_64K> NokiaN82_Terminal_Portrait_64K;
        typedef GraphicTerminalLandscapeImpl<NokiaN82_Landscape_64K> NokiaN82_Terminal_Landscape_64K;

        typedef GraphicTerminalPortraitImpl<NokiaN82_Portrait_262K> NokiaN82_Terminal_Portrait_262K;
        typedef GraphicTerminalLandscapeImpl<NokiaN82_Landscape_262K> NokiaN82_Terminal_Landscape_262K;

        typedef GraphicTerminalPortraitImpl<NokiaN82_Portrait_16M> NokiaN82_Terminal_Portrait_16M;
        typedef GraphicTerminalLandscapeImpl<NokiaN82_Landscape_16M> NokiaN82_Terminal_Landscape_16M;

        /*
         * ILI9327 400x240 interface: 64K and 262K colours, portrait and landscape
         */

        typedef GraphicsLibrary<ILI9327<PORTRAIT,COLOURS_16BIT,Fsmc16BitAccessMode,ILI9327400x240PanelTraits>,Fsmc16BitAccessMode> ILI9327_400x240_Portrait_64K;
        typedef GraphicsLibrary<ILI9327<LANDSCAPE,COLOURS_16BIT,Fsmc16BitAccessMode,ILI9327400x240PanelTraits>,Fsmc16BitAccessMode> ILI9327_400x240_Landscape_64K;

        typedef GraphicsLibrary<ILI9327<PORTRAIT,COLOURS_18BIT,Fsmc16BitAccessMode,ILI9327400x240PanelTraits>,Fsmc16BitAccessMode> ILI9327_400x240_Portrait_262K;
        typedef GraphicsLibrary<ILI9327<LANDSCAPE,COLOURS_18BIT,Fsmc16BitAccessMode,ILI9327400x240PanelTraits>,Fsmc16BitAccessMode> ILI9327_400x240_Landscape_262K;

        typedef GraphicTerminalPortraitImpl<ILI9327_400x240_Portrait_64K> ILI9327_400x240_Terminal_Portrait_64K;
        typedef GraphicTerminalLandscapeImpl<ILI9327_400x240_Landscape_64K> ILI9327_400x240_Terminal_Landscape_64K;

        typedef GraphicTerminalPortraitImpl<ILI9327_400x240_Portrait_262K> ILI9327_400x240_Terminal_Portrait_262K;
        typedef GraphicTerminalLandscapeImpl<ILI9327_400x240_Landscape_262K> ILI9327_400x240_Terminal_Landscape_262K;
    }
}
