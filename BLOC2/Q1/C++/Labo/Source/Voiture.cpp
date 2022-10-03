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
    modele = new Modele;
}

Voiture::Voiture(const Voiture &voiture)
{
    #ifdef DEBUG
        cout << "Constructeur de copie de Voiture" << endl;
    #endif
    

}
