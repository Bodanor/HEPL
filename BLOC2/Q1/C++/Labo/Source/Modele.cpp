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

        cout << "Constructeur d'initialisation de Modele" << endl;

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

        cout << "Constructeur de copie de Modele" << endl;

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
    if (nom)
        delete [] nom;
    nom = new char [50];
    strcpy(nom, modele.nom);
    moteur = modele.moteur;
    prix = modele.prix;
}

ostream& operator<<(ostream& s, const Modele& modele)
{
    s << "Nom : "<<modele.nom << endl;
    s << "Puissance : "<< modele.puissance << endl;
    s << "Moteur : ";

    switch (modele.moteur)
    {
    case Essence : 
        s <<"Essence ";
        break;
    case Diesel:
        s <<"Diesel ";
        break;
    case Electrique:
        s << "Electrique ";
        break;
    case Hybride:
        s << "Hybride ";
        break;
    default:
        s << "Inconnu ";
        break;
    }
    s << endl;
    s << "Prix : " << modele.prix << "Euros" << endl;

    return s;


}
istream& operator>>(istream& s, Modele& modele)
{
    int moteur;

    cout << "Nom : ";
    s >> modele.nom;
    cout << "Moteur : ";
    s >> moteur;
    if (moteur >= 0 && moteur <=3)
        modele.moteur = (Moteur)moteur;
    cout << "Puissance : ";
    s >> modele.puissance;
    cout << "Prix : ";
    s >> modele.prix;

    return s;
}

void Modele::Save(ostream &fichier) const
{
	int size_nom = strlen(nom);
    
	if (!fichier)
		cout << "Impossible de sauvegarder le fichier !"<< endl;
	else {
       
		fichier.write((char*)&size_nom, sizeof(int));
		fichier.write(nom, strlen(nom)*sizeof(char));
		fichier.write((char*)&puissance, sizeof(puissance));
		fichier.write((char*)&moteur, sizeof(moteur));
		fichier.write((char*)&prix, sizeof(prix));
	}
    
}

void Modele::Load(istream &fichier)
{
	int size_nom;
   

	if (!fichier)
		cout << "Impossible de lire le fichier !"<<endl;
	else {
        
		fichier.read((char*)&size_nom, sizeof(int));
		nom = new char [size_nom + 1];
		fichier.read((char*)nom, size_nom*sizeof(char));
		nom[size_nom] = '\0';
		fichier.read((char*)&puissance, sizeof(puissance));
		fichier.read((char*)&moteur, sizeof(moteur));
		fichier.read((char*)&prix, sizeof(prix));
		
	}
   
}
