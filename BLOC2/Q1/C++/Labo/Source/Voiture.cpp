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
    for (unsigned long i = 0; i < (sizeof(options)/sizeof(options[0])); i++)
        if (voiture.options[i] != NULL)
            options[i] = new Option(*voiture.options[i]);
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
    int nb_options = 0;

    cout << "Nom de voiture :" << nom << endl;
    modele.Affiche();

    for (unsigned long i = 0; i < (sizeof(options)/sizeof(options[0])); i++)
    {
        if (options[i] != NULL)
            nb_options++;
    }

    cout << "Nombre total d'options : " << nb_options << endl;

    for (unsigned long i = 0; i < (sizeof(options) / sizeof(options[0])); i++)
        if (options[i] != NULL)
            options[i]->Affiche();
}

Voiture::~Voiture()
{
    #ifdef DEBUG
        cout << "Deconstructeur de Voiture" << endl;
    #endif

    for (unsigned long i = 0; i < (sizeof(options)/sizeof(options[0])); i++)
        if (options[i] != NULL)
            delete options[i];
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
    modele = modele_voiture;
}

const Modele Voiture::getModele() const
{
    return modele;
}

void Voiture::AjouteOption(const Option & opt)
{
    unsigned long i = 0;

    while (i < (sizeof(options)/sizeof(options[0])) && options[i] != NULL)
        i++;
    if (i < (sizeof(options)/sizeof(options[0]))){
        options[i] = new Option(opt);
    }

}

void Voiture::RetireOption(string code)
{
    unsigned long i = 0;
    while (i < (sizeof(options)/sizeof(options[0])) && options[i] != NULL && options[i]->getCode() != code)
        i++;

    if (i < (sizeof(options)/sizeof(options[0])) && options[i] != NULL && options[i]->getCode() == code)
    {
        delete options[i];
        options[i] = NULL;
    }
}

float Voiture::getPrix()
{
    float prix_total = modele.getPrixDeBase();
    
    for (unsigned long i = 0; i < (sizeof(options)/sizeof(options[0])); i++)
    {
        if (options[i] != NULL)
            prix_total += options[i]->getPrix();
    }

    return prix_total;

}
