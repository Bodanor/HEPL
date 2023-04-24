#ifndef __PASSWORD_EXCEPTION_H__
#define __PASSWORD_EXCEPTION_H__

#include <iostream>
#include <string>

#include "Exception.h"

using namespace std;

class PasswordException : public Exception
{
    private:
        int code;
    
    public:
        PasswordException();
        PasswordException(const string mesage, const int c);
        PasswordException(const PasswordException &);
        ~PasswordException();

        void setCode(const int c);
        int getCode() const;

        static const int INVALID_LENGHT;
        static const int ALPHA_MISSING;
        static const int DIGIT_MISSING;
        static const int NO_PASSWORD;
};

#endif