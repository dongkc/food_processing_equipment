/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "display/Terminal.h"
#include "stream/OutputStream.h"

namespace stm32plus {

    /**
     * @brief Output stream for writing to terminals
     * @tparam TType The actual terminal implementation class being used.
     */

    template<class TType>
    class TerminalOutputStream : public OutputStream {

        protected:
            display::Terminal<TType>& _terminal;

        public:

            /**
             * Constructor.
             * @param[in] term_ The terminal object, which must be of the same type as this class's template parameter.
             *         Caller supplied object, must not go out of scope.
             */

            TerminalOutputStream(display::Terminal<TType>& term_) :
                _terminal(term_) {
            }

            // overrides from OutputStream

            virtual bool write(uint8_t c_) {
                _terminal.writeChar(static_cast<char> (c_));
                return true;
            }

            virtual bool write(const void *buffer_,uint32_t size_) {
                const char *ptr;

                ptr=static_cast<const char *> (buffer_);
                while(size_--)
                    _terminal.writeChar(*ptr++);

                return true;
            }

            virtual bool close() {
                return true;
            }

            virtual bool flush() {
                return true;
            }
    };
}
