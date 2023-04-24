#ifndef __CLIENT_H__
#define __CLIENT_H__
#include <iostream>
#include <string>
#include "Vecteur.h"

#include "Intervenant.h"

class Client : public Intervenant
{
    friend ostream& operator<<(ostream&, const Client &);
    private:
        string gsm;
        int cmpClient(const Client &);
    
    public:
        Client();
        Client(const string, const string, const int, const string);
        Client(const Client&);
        ~Client();

        string ToString() const;
        string Tuple() const;

        void setGsm(string);
        int getNumero() const;
        string getGsm() const;

        Client& operator=(const Client&);
        int operator<(const Client&);
        int operator==(const Client&);
        int operator>(const Client&);

};

#endif