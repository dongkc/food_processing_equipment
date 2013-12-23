/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include <stdint.h>
#include <cstdlib>
#include "memory/MEM_DataCopy.h"


namespace stm32plus {


/**
 * @brief Template class to manage a block of data on the heap
 * @tparam T The type being managed here.
 *
 * Assignment makes a copy and does not transfer ownership of the original. Therefore a=b
 * will make a new copy of b. Memory is copied from b to a using memcpy so obviously this
 * only works with simple types and structures.
 */

    template<typename T>
    class Memblock {

        private:
            T *_data;
            uint32_t _size;

        public:

            /**
             * Default constructor
             */

            Memblock() {
                _data=NULL;
                _size=0;
            }


            /**
             * Construct with space for the given number of types.
             * @param[in] numTypes_ The number of types to store here.
             */

            Memblock(uint32_t numTypes_) {
                allocate(numTypes_);
            }


            /**
             * Copy constructor.
             * @param[in] src_ The memory block to copy from
             */

            Memblock(const Memblock<T>& src_) {
                assign(src_);
            }


            /**
             * Destructor, de-allocate memory
             */

            ~Memblock() {
                cleanup();
            }


            /**
             * Get a pointer to the data block.
             * @return A pointer.
             */

      T *getData() const {
        return _data;
      }


      /**
       * Get the number of types being stored here.
       * @return The number of types.
       */

            uint32_t getSize() const {
                return _size;
            }


            /**
             * Cast operator
             * @return A pointer to the data.
             */

            operator T* () {
                return _data;
            }


            /**
             * Assignment operator.
             * @param[in] src_ The block to assign from.
             * @return A reference to this.
             */

            Memblock<T>& operator=(const Memblock<T>& src_) {
                cleanup();
                assign(src_);

                return *this;
            }


            /**
             * Array access operator.
             * @param[in] pos_ The index in the block to return.
             * @return A reference to the item at the index.
             */

            T& operator[](int pos_) const {
                return _data[pos_];
            }


            /**
             * Reallocate to handle new data. Only increases are supported.
             * @param[in] newSize The size to increase to.
             */

            void reallocate(uint32_t newSize) {
                T *newData;

                if(_data==NULL)
                    allocate(newSize);
                else {
                    newData=new T[newSize];
                    MEM_DataCopy(newData,_data,_size*sizeof(T));
                    delete [] _data;
                    _data=newData;
                    _size=newSize;
                }
            }

            /**
             * Free existing data and start with a fresh buffer of the given size
             * @param[in] resetSize The size to start again with
             */

            void reset(uint32_t resetSize) {
                cleanup();
                allocate(resetSize);
            }

        private:

            void allocate(uint32_t numTypes_) {
                _data=new T[numTypes_];
                _size=numTypes_;
            }

            void cleanup() {
                if(_data!=NULL) {
                    delete [] _data;
                    _data=NULL;
                    _size=0;
                }
            }

            void assign(const Memblock<T>& src_) {
                _data=new T[src_.getSize()];
                _size=src_.getSize();
                MEM_DataCopy(_data,const_cast<Memblock<T>&>(src_),_size*sizeof(T));
            }
    };


    /// Typedef for the common case of a block of bytes
    typedef Memblock<uint8_t> ByteMemblock;
}
