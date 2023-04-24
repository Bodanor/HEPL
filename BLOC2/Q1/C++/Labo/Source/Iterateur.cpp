#include "Iterateur.h"

template <class T> Iterateur<T>::Iterateur(Vecteur<T>& src) : vec(src), v(src.v)
{

};

template <class T> Iterateur<T>::~Iterateur()
{

}
template <class T> void Iterateur<T>::reset(void)
{
    v = vec.v;

}

template <class T> bool Iterateur<T>::end(void)
{
   return (v - vec.v >= vec._size ) ? 1 : 0;

}

template <class T> bool Iterateur<T>::operator++()
{
    if (!end()){
        v++;
        return true;
    }
    return false;

}

template <class T> bool Iterateur<T>::operator++(int)
{
    return operator++();
}

template <class T> Iterateur<T>::operator T() const
{
    return *v;

}
template class Iterateur<int>;
template class Iterateur<Client>;