#include "PasswordException.h"

const int PasswordException::INVALID_LENGHT = 0;
const int PasswordException::ALPHA_MISSING = 1;
const int PasswordException::DIGIT_MISSING = 2;
const int PasswordException::NO_PASSWORD = 3;

PasswordException::PasswordException() : Exception()
{
    #ifdef DEBUG
        cout << "Contruscteur par defaut de PasswordException" << endl;
    #endif


}

PasswordException::PasswordException(const string msg, const int c) : Exception(msg)
{
    #ifdef DEBUG
        cout << "Contruscteur d'initialisation de PasswordException" << endl;
    #endif

    setCode(c);
}

PasswordException::PasswordException(const PasswordException &src) : Exception(src)
{
    #ifdef DEBUG
        cout << "Contruscteur de copie de PasswordException" << endl;
    #endif

    setCode(src.getCode());
}
PasswordException::~PasswordException()
{
    #ifdef DEBUG
        cout << "Destructeur de PasswordException" << endl;
    #endif


}
void PasswordException::setCode(const int c)
{
    code = c;
}


int PasswordException::getCode() const
{
    return code;
}
