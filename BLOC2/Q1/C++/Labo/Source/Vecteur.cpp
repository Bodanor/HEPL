#include "Vecteur.h"

template <class T> Vecteur<T>::Vecteur(void)
{
    _sizeMax = 10;
    _size = 0;

    v = new T[10];
}

template <class T> Vecteur<T>::Vecteur(const int size)
{
    _sizeMax = size;
    _size = 0;

    v = new T[size];
}

template <class T> Vecteur<T>::Vecteur(const Vecteur &vec)
{
    _sizeMax = vec.sizeMax();
    _size = vec.size();

    v = new T[_sizeMax];

    for(int i = 0; i < _size; i++)
        v[i] = vec[i];
}

template <class T> Vecteur<T>::~Vecteur(void)
{
    delete []v;
}

template <class T> int Vecteur<T>::size() const
{
    return _size;
}

template <class T> int Vecteur<T>::sizeMax() const
{
    return _sizeMax;
}

template <class T> void Vecteur<T>::Affiche() const
{
    for (int i = 0; i < _size; i++)
        cout << v[i] <<endl;
}

template <class T> void Vecteur<T>::insere(const T& src)
{
    if (_size < _sizeMax)
        *(v+_size) = src;
    _size++;

}

template <class T> T Vecteur<T>::retire(const int index)
{
    T tmp;
    if (index >= 0 && index < _sizeMax - 1)
        tmp = *(v + index);
    // Potentiellement debordement de tableau !
    for (int i = index; i < _sizeMax - 1; i++)
        *(v + i) = *(v + i + 1);
    
    _size--;
    return tmp;


}

template <class T> Vecteur<T> & Vecteur<T>::operator=(const Vecteur & vec)
{
    _size = vec._size;
    _sizeMax = vec._sizeMax;
    if (v != NULL)
        delete [] v ;
    v = new T[vec._sizeMax];

    for (int i = 0; i < vec._size; i++)
        *(v + i) = *(vec.v + i);
    
    return (*this);
    

}

template <class T> T& Vecteur<T>::operator[](int i) const
{
    return *(v + i);
}

/** Instanciation des templates...*/

template class Vecteur<int>;
template class Vecteur<Client>;
template class Vecteur<Employe>;
template class Vecteur<Modele>;
template class Vecteur<Option>;