#include "Personne.h"

Personne::Personne()
{
    #ifdef DEBUG
    cout << "Constructeur par défaut de Personne" << endl;

    #endif

    setNom("Sans nom");
    setPrenom("Sans prenom");
}

Personne::Personne(const string nom_pers, const string prenom_pers)
{
    setNom(nom_pers);
    setPrenom(prenom_pers);
}

Personne::Personne(const Personne& pers)
{
    setNom(pers.getNom());
    setPrenom(pers.getPrenom());

}

Personne::~Personne()
{
    #ifdef DEBUG
        cout << "Deconstructeur de Personne" << endl;
    #endif
    
}
void Personne::setNom(string nom_pers)
{
    nom = nom_pers;
}

void Personne::setPrenom(string prenom_pers)
{
    prenom = prenom_pers;
}

string Personne::getNom() const
{
    return nom;

}

string Personne::getPrenom() const
{
    return prenom;
}

void Personne::Affiche() const
{
    cout << "Nom : " << getNom() << endl;
    cout << "Prenom : " << getPrenom() << endl;
}

ostream& operator<<(ostream& s, const Personne& pers)
{
    s << "Nom : " << pers.getNom() << endl;
    s << "Prenom : " << pers.getPrenom() << endl;
    return s;
}

istream& operator>>(istream& s, Personne& pers)
{
    cout << "Nom : ";
    s >> pers.nom;
    cout << "Prenom : ";
    s >> pers.prenom;

    return s;
}

Personne& Personne::operator=(const Personne& pers)
{
    nom = pers.getNom();
    prenom = pers.getPrenom();

    return (*this);
}