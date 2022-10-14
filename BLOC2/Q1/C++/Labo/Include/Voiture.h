#ifndef VOITURE_H
#define VOITURE_H

#include <string>
#include "Modele.h"
#include "Option.h"

using namespace std;

class Voiture
{
    private:
        string nom;
        Modele modele;
        Option *options [5] = {0};
        
    public:
        Voiture();
        Voiture(const Voiture &);
        Voiture(const string, Modele);
        ~Voiture();

        Voiture& operator=(const Voiture&);
        
        const string getNom()const;
        void setNom(string);
        void Affiche()const;
        void setModele(const Modele &);
        const Modele getModele() const;
        void Affiche();

        void AjouteOption(const Option &);
        void RetireOption(string code);
        float getPrix();

        
    
};
#endif
