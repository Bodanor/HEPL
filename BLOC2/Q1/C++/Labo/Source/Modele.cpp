#include "Modele.h"
#include <iostream>
#include <ostream>
#include <string.h>

using namespace std;

/******************************Constructeur et destructeur***************************/

Modele::Modele()
{
    #ifdef DEBUG

        cout << "Construscteur par défaut de Modele" << endl;

    #endif 

    puissance = 0;
    prix = 0;
    moteur = Essence;

    nom = new char [50];
    strcpy(nom, "Modele sans nom");

}

/********************************Getters et Setters**********************************/

const char * Modele::getNom()const
{
    return nom;
}

int Modele::getPuissance()const
{
    return puissance;
}

Moteur Modele:: getMoteur()const
{
    return moteur;
}

float Modele::getPrixDeBase()const
{
    return prix;
}

void Modele::setNom(const char *n)
{
    if(nom!=NULL)
        delete[] nom;
    nom = new char [strlen(n)+1];
    strcpy(nom, n);
}

void Modele::setPuissance(int p)
{
    if(p>=0)
        puissance = p;
}

void Modele::setMoteur(Moteur m)
{
    moteur = m;
}

void Modele::setPrixDeBase(float pr)
{
    prix = pr;
}



Modele:: Modele(const char *n, int p, Moteur m, float pr)
{
    #ifdef DEBUG

        cout << "Construscteur d'initialisation de Modele" << endl;

    #endif 

    nom = NULL;
    setNom(n);
    setPuissance(p);
    setMoteur(m);
    setPrixDeBase(pr);
}

Modele::Modele(const Modele &source)
{
    #ifdef DEBUG

        cout << "Construscteur de copie de Modele" << endl;

    #endif 

    nom = NULL;
    setNom(source.getNom());
    setPuissance(source.getPuissance());
    setMoteur(source.getMoteur());
    setPrixDeBase(source.getPrixDeBase()); 
}

Modele::~Modele()
{
    #ifdef DEBUG

        cout << "Deconstructeur de Modele" << endl;

    #endif

    if(nom)
        delete[]nom;
}

/*********************************Méthode publique***********************************/

void Modele::Affiche()const
{
    cout<< "Nom : "<<nom << endl;
    cout << "Puissance : "<< puissance << endl;
    cout << "Moteur : ";

    switch (moteur)
    {
    case Essence : 
        cout<<"Essence ";
        break;
    case Diesel:
        cout <<"Diesel ";
        break;
    case Electrique:
        cout << "Electrique ";
        break;
    case Hybride:
        cout << "Hybride ";
        break;
    default:
        cout << "Inconnu ";
        break;
    }
    cout << endl;
    cout << "Prix : " << prix << "Euros" << endl;

}
void Modele::operator=(Modele modele)
{
    puissance = modele.puissance;
    nom = new char [50];
    strcpy(nom, modele.nom);
    moteur = modele.moteur;
    prix = modele.prix;
}
