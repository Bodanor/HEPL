#ifndef __VECTEURTRIE_H__
#define __VECTEURTRIE_H__

#include "Vecteur.h"
#include <bits/stdc++.h>
using namespace std;

template <class T> class VecteurTrie : public Vecteur<T>
{
    public:
        VecteurTrie();
        VecteurTrie(const int);
        void insere(const T&);

};


#endif