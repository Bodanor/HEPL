#ifndef __INTERVENANT_H
#define __INTERVENANT_H

#include <iostream>
#include <string>

#include "Personne.h"

using namespace std;

class Intervenant : public Personne
{
    protected:
        int numero;
    
    public:
        Intervenant();
        virtual ~Intervenant();
        Intervenant(const string, const string, int);
        Intervenant(const Intervenant &);
        void setNumero(int);
        int getNumero() const;
        virtual string ToString() const = 0;
        virtual string Tuple() const = 0;

    
};

#endif