/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#ifndef __F9BEC383_7F73_48C6_A168D84DF0B9BFAA
#define __F9BEC383_7F73_48C6_A168D84DF0B9BFAA


namespace stm32plus
{
    namespace ili9325
    {
        namespace DrivingWaveControlCmd
        {
            enum
            {
                Opcode = 2,
                FixedBits = 1<<10,

                EOR = 1<<8,
                BC = 1<<9
            };
        }
    }
}


#endif /* STARTOSCILLATIONCOMMAND_H_ */
