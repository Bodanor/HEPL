#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <iostream>
#include <string>

using namespace std;

class Exception
{
    private:
        string message;
    
    public:
        Exception();
        Exception(const string &);
        Exception(const Exception &);
        ~Exception();

        const string getMessage() const ;
        void setMessage(const string &);

};
#endif
