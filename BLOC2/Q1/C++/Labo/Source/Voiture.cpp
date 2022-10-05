#include "Voiture.h"
#include "Modele.h"

#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

Voiture::Voiture()
{
    #ifdef DEBUG
    cout << "Constructeur par défaut de Voiture" << endl;

    #endif
    
    nom = "Voiture sans nom";
}

Voiture::Voiture(const Voiture &voiture)
{
    #ifdef DEBUG
        cout << "Constructeur de copie de Voiture" << endl;
    #endif

    setNom(voiture.getNom());
    setModele(voiture.getModele());
}

Voiture::Voiture(string nom, Modele modele_voiture)
{
    #ifdef DEBUG
        cout << "Constructeur de copie de Voiture" << endl;
    #endif

    setNom(nom);
    setModele(modele_voiture);

}

void Voiture::Affiche()
{
    cout << "Nom de voiture :" << nom << endl;
    modele.Affiche();
}

Voiture::~Voiture()
{
    #ifdef DEBUG
        cout << "Deconstructeur de Voiture" << endl;
    #endif
}

const string Voiture::getNom() const
{
    return nom;
}
void Voiture::setNom(string nom_voiture)
{
    nom = nom_voiture;
}

void Voiture::setModele(const Modele &modele_voiture)
{
    /* Parce que le compilateur sais pas comment faire modele = modele ?
     * Dois je copier chaque champs de modele ?
    */
    modele = modele_voiture;
}

const Modele Voiture::getModele() const
{
    return modele;
}
