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

    unsigned int i = 0;

    while (i < (sizeof(options)/sizeof(options[0])))
    {
        if (voiture.options[i] != NULL){
            AjouteOption(*voiture.options[i]);
        }
        i++;
    }


 
}

Voiture::Voiture(string nom, Modele modele_voiture)
{
    #ifdef DEBUG
        cout << "Constructeur de copie de Voiture" << endl;
    #endif

    setNom(nom);
    setModele(modele_voiture);

}

void Voiture::Affiche() const
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
    
    cout << "Prix total du projet : " << getPrix() << endl;
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
    if (i < (sizeof(options)/sizeof(options[0])) && options[i] == NULL){
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

float Voiture::getPrix() const
{
    float prix_total = modele.getPrixDeBase();
    
    for (unsigned long i = 0; i < (sizeof(options)/sizeof(options[0])); i++)
    {
        if (options[i] != NULL)
            prix_total += options[i]->getPrix();
    }

    return prix_total;

}

Voiture& Voiture::operator=(const Voiture &source)
{
    nom = source.getNom();
    modele = source.getModele();

    for (unsigned int i = 0; i < (sizeof(options)/sizeof(options[0])); i++)
    {
        if (options[i] != NULL)
        {
            delete options[i];
        }
        if (source.options[i] == NULL)
            options[i] = NULL;
        else
            options[i] = new Option(*source.options[i]);
    }

    return (*this);

}

Voiture Voiture::operator+(Option opt) const 
{
    Voiture tmp(*this);
    
    tmp.AjouteOption(opt);

    return tmp;

}

Voiture operator+(const Option& opt, const Voiture& src)
{
    return src + opt;
}

Voiture Voiture::operator-(Option opt) const
{
    Voiture tmp(*this);
    tmp.RetireOption(opt.getCode());

    return tmp;
}

Voiture operator-(const Option& opt, const Voiture& src)
{
    return src-opt;
}
Voiture Voiture::operator-(const string& opt) const
{
    Voiture tmp(*this);
   
    tmp.RetireOption(opt);

    return tmp;
}

int Voiture::operator<(const Voiture& src) const
{
    if (getPrix() < src.getPrix())
        return 1;
    else
        return 0;

}

int Voiture::operator>(const Voiture& src) const
{
    if (getPrix() > src.getPrix())
        return 1;
    else
        return 0;

}

int Voiture::operator==(const Voiture& src) const
{
    if (getPrix() == src.getPrix())
        return 1;
    else
        return 0;

}
ostream& operator<<(ostream& s, const Voiture& voiture)
{
    voiture.Affiche();
    return s;


}

Option* Voiture::operator[](int index) const
{
    return options[index];

}