#ifndef __ITERATEUR_H__
#define __ITERATEUR_H__

#include "Vecteur.h"

using namespace std;

template <class T> class Iterateur
{
    private:
        Vecteur<T>& vec;
        T *v;
    

    public:
        Iterateur(Vecteur<T>&);
        ~Iterateur();
        void reset(void);
        bool end(void);
        bool operator++();
        bool operator++(int);
        operator T()const;

};

#endif
