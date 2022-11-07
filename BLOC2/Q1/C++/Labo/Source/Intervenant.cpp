#include "Intervenant.h"

Intervenant::Intervenant() : Personne()
{
    #ifdef DEBUG
    cout << "Constructeur par défaut de Intervenant" << endl;

    #endif

    setNumero(-1);
}

Intervenant::Intervenant(const string nom_pers, const string prenom_pers, int num_pers) : Personne(nom_pers, prenom_pers)
{
    setNumero(num_pers);
}

Intervenant::~Intervenant()
{
    #ifdef DEBUG
        cout << "Deconstructeur de Intervenant" << endl;
    #endif

    
}

void Intervenant::setNumero(int num_pers)
{
    numero = num_pers;
}

int Intervenant::getNumero() const
{
    return numero;
}