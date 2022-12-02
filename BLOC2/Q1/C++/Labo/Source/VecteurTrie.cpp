#include "VecteurTrie.h"

template <class T> VecteurTrie<T>::VecteurTrie() : Vecteur<T>()
{

}
template <class T> VecteurTrie<T>::VecteurTrie(const int size) : Vecteur<T>(size)
{

}

template <class T> void VecteurTrie<T>::insere(const T& src) 
{
    Vecteur<T>::insere(src);
    /*
    * Explication du This : 
    * 
    * This is called Two-phase name lookup.
    * Meme si '_size' est private, le fait d'utiliser un template fait que son nom n'est pas dépendant.
    * I.E : Il ne depend pas du paramètre du template. ici, il faut forcer le fait qu'il soit dépedant d'ou le 'this',qui une fois
    * le template instancier aura un type donc le compilateur sauras associer la variable dès l'instanciation.
    * Pour plus d'informations : https://womble.decadent.org.uk/c++/template-faq.html#two-phase 
    */
   

   std::sort((this->v), (this->v + this->_size));

}

template class VecteurTrie<int>;
template class VecteurTrie<Client>;