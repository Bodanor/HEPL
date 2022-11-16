#include "Exception.h"

Exception::Exception()
{
    #ifdef DEBUG
        cout << "Contruscteur par default de Exception" << endl;
    #endif

    message = "";

}

Exception::Exception(const string &msg)
{
    #ifdef DEBUG
        cout << "Contruscteur d'initialisation de Exception" << endl;
    #endif

    message = msg;
}

Exception::Exception(const Exception &src)
{
    #ifdef DEBUG
        cout << "Contruscteur de copie de Exception" << endl;
    #endif

    message = src.getMessage();

}

Exception::~Exception()
{
    #ifdef DEBUG
        cout << "Destructeur de Exception" << endl;
    #endif

}
const string Exception::getMessage() const 
{
    return message;

}

void Exception::setMessage(const string &msg)
{
    message = msg;

}