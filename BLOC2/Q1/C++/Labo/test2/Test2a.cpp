#include <iostream>
using namespace std;
#include "Modele.h"
#include "Voiture.h"

// Tests de base de la classe Voiture (sans les options)

int main()
{
  cout << endl << "(1) ***** Test du constructeur par defaut de Voiture *******************************" << endl;
  {
    Voiture voiture;
    voiture.Affiche();
  }

  cout << endl << "(2) ***** Test des setters/getters *************************************************" << endl;
  {
    Voiture v;
    v.setNom("Projet_208_MrDugenou");
    Modele m("208 Active 1.5 BlueHDi 5P",100,Diesel,21800.0f);
    v.setModele(m);
    v.Affiche();
    cout << "Nom du projet : " << v.getNom() << endl;
    cout << "Modele du projet : ";
    v.getModele().Affiche();
  }

  //cout << endl << "(3) ***** Test du constructeur d'initialisation de Voiture *************************" << endl;
  //{
  //  Voiture v("Projet_508SW_MmeLoreille",Modele("508SW Style 1.6 HDi",115,Diesel,28500.0f));
  //  v.Affiche();
  //  cout << "Nom du projet : " << v.getNom() << endl;
  //  cout << "Modele du projet : ";
  //  v.getModele().Affiche();
  //}

  //cout << endl << "(4) ***** Test du constructeur de copie de Voiture *********************************" << endl;
  //{
  //  Voiture v1("Projet_208GTi_MrLepresse",Modele("208 GTi 1.6",200,Essence,34100.0f));
  //  cout << "v1 (AVANT) :" << endl;
  //  v1.Affiche();
  //  {   
  //    Voiture v2(v1);
  //    cout << "v2 :" << endl;
  //    v2.Affiche();
  //    v2.setNom("Projet_208GTi_MrLepresse_bis");
  //    v2.Affiche();
  //  }
  //  cout << "v1 (APRES) :" << endl;
  //  v1.Affiche();
  //}

  return 0;
}


