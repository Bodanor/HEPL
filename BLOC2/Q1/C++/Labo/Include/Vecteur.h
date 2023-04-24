#ifndef __VECTEUR_H__
#define __VECTEUR_H__

#include <iostream>
#include "Client.h"
#include "Option.h"
#include "Modele.h"
#include "Employe.h"

using namespace std;

template <class T> class Iterateur;
template <class T> class Vecteur
{
    protected:
        T *v;
        int _sizeMax;
        int _size;
    
    public:
        Vecteur();
        Vecteur(const int size);
        Vecteur(const Vecteur&);
        ~Vecteur();
        int size(void) const;
        int sizeMax(void) const;
        void Affiche(void) const;
        void insere(const T&);
        T retire(const int);

        Vecteur& operator=(const Vecteur&);
        T& operator[](int) const;

        friend class Iterateur<T>;
};

#endif