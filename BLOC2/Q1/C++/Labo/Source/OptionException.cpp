#include "OptionException.h"

OptionException::OptionException() : Exception()
{
    #ifdef DEBUG
        cout << "Contructeur par defaut de OptionException" << endl;
    #endif


}
OptionException::OptionException(const string &msg)  : Exception(msg)
{
    #ifdef DEBUG
        cout << "Contruscteur d'initialisation de OptionException" << endl;
    #endif

}

OptionException::OptionException(const Exception& src) : Exception(src)
{
    #ifdef DEBUG
        cout << "Contruscteur de copie de OptionException" << endl;
    #endif
    
} 
OptionException::~OptionException()
{
    #ifdef DEBUG
        cout << "Destructeur de OptionException" << endl;
    #endif

}