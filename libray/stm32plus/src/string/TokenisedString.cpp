/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "string/TokenisedString.h"
#include <cstring>
#include <cstdlib>


namespace stm32plus {

    /**
     * Constructor.
     * @param[in] original_ The original string. This string is not modified.
     * @param[in] separators_ The token separators.
     */

    TokenisedString::TokenisedString(const char *original_,const char *separators_) {

        char *ptr,*current;
        int i;

    // count tokens

        _numTokens=0;
        _first=0;
        _last=-1;
        _tokens=NULL;

        if(original_==NULL)
            return;

        ptr=strdup(original_);
        current=strtok(ptr,separators_);

        while(current!=NULL) {
            _numTokens++;
            current=strtok(NULL,separators_);
        }
        free(ptr);

    // anything?

        if(_numTokens==0)
            return;

    // allocate

        _tokens=new char *[_numTokens];

    // parse again

        ptr=strdup(original_);
        current=strtok(ptr,separators_);
        i=0;

        while(current!=NULL) {
            _tokens[i++]=strdup(current);
            current=strtok(NULL,separators_);
        }
        free(ptr);

        _last=_numTokens-1;
    }


    /**
     * Destructor. Free memory used by tokens.
     */

    TokenisedString::~TokenisedString() {

        int i;

        if(_numTokens>0) {
            for(i=0;i<_numTokens;i++)
                free(_tokens[i]);

            delete [] _tokens;
        }
    }

    /**
     * Get the number of tokens, taking into account the range if set.
     * @return The number of tokens.
     */

    int TokenisedString::getNumTokens() const {
        return (_last-_first)+1;
    }


    /**
     * Get a token, taking into account the range if set.
     * @param[in] pos_ The token index to get.
     * @return An internal pointer to the token.
     */

    const char *TokenisedString::operator[](int pos_) const {
        return _tokens[_first+pos_];
    }


    /**
     * Return the last entry.
     * @return The last token.
     */

    const char *TokenisedString::last() const {
        return _tokens[_last];
    }


    /**
     * Limit the range of tokens returned so that the caller can only see a subset of all the tokens.
     * @param[in] first_ The first token in the range.
     * @param[in] last_ The last token in the range.
     */

    void TokenisedString::setRange(int first_,int last_) {
        _first=first_;
        _last=last_;
    }


    /**
     * Clear the range parameters.
     */

    void TokenisedString::resetRange() {
        _first=0;
        _last=_numTokens-1;
    }
}
