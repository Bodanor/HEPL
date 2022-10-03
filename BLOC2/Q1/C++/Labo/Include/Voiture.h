#ifndef VOITURE_H
#define VOITURE_H

#include <string>
#include "Modele.h"

using namespace std;

class Voiture
{
    private:
        string nom;
        Modele *modele;
    
    public:
       Voiture();
       Voiture(const Voiture &);
       Voiture(const string, Modele);
        ~Voiture();
        const string getNom()const;
        void Affiche()const;

        
    
};

#endif
