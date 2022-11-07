#ifndef __CLIENT_H__
#define __CLIENT_H__
#include <iostream>
#include <string>

#include "Intervenant.h"

class Client : public Intervenant
{
    private:
        string gsm;
    
    public:
        Client();
        Client(const string, const string, const int, const string);
        Client(const Client&);
        ~Client();

        string ToString() const;
        string Tuple() const;
        void setNumero(int);
        void setGsm(string);
        int getNumero() const;
        string getGsm() const;

        Client& operator=(const Client&);

};

#endif