#ifndef __OPTION_EXCEPTION_H__
#define __OPTION_EXCEPTION_H__

#include <iostream>
#include <string>

#include "Exception.h"

class OptionException : public Exception
{
    public:
        OptionException();
        OptionException(const Exception&);
        OptionException(const string &);
        ~OptionException();

};

#endif