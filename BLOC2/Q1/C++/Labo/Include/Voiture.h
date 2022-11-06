#ifndef VOITURE_H
#define VOITURE_H

#include <string>
#include "Modele.h"
#include "Option.h"

using namespace std;

class Voiture
{
    /**
     * Note importante à moi même:
     * Dans le livre on nous dit que "friend" est utilise lorsque les operandes sont des objets de type différent qui peuvent e présenter dans n'importe quel ordre.
     * Si par exemple on souhaite faire v1 = v1 + opt, alors pas besoin de friend puisque la premiere operande est de type voiture et donc une surcharge membre est
     * suffisante. Mais si on a v1 = opt + v1 alors on nous dit que nous devoit soit utiliser friend OU un operateur membre de la classe "opt" avec
     * comme seconde operande "Voiture". Donc j'ai effectuer des test pour surcharger l'operateur '+' dans la classe Option et dans la classe Voiture. Naturellement,
     * Cela pose un problème puisque j'avais au final une dépendance circulaire... En effet, la classe Voiture à besoin de la classe Option et la classe Option
     * à besoin de la classe Voiture (Voiture --> #include #"Options.h"; Option --> #include "Voiture.h" ce qui donne une dependance circulaire !)
     * La solution est la suivante, garder les includes comme explique juste avant MAIS, il faut avoir une "Forward declaration", ce qui veux dire que dans le fichier
     * Voiture avant la classe "voiture" il faut ajouter la ligne "Class Option;", meme chose dans Option ("Class Voiture;"). En gros declarer explicitement les classes.
     * En générale, les dependances cirtulaire sont à eviter mais ici je me suis imaginer comment on pourrait par exemple surcharger la classe <int> pour additionner
     * un int et une voiture.
     * 
     * Voici le post qui m'a le plus aider pour comprendre comment parvenir à la solution similaire à "friend ":
     * https://stackoverflow.com/questions/15992461/overloading-operator-between-objects-of-more-than-two-classes
     * 
     * 
     */
    friend Voiture operator+(Option, Voiture);
    friend Voiture operator-(Option, Voiture);


    private:
        string nom;
        Modele modele;
        Option *options [5] = {0};
        
    public:
        Voiture();
        Voiture(const Voiture &);
        Voiture(const string, Modele);
        ~Voiture();

        Voiture& operator=(const Voiture&);
        
        const string getNom()const;
        void setNom(string);
        void Affiche()const;
        void setModele(const Modele &);
        const Modele getModele() const;
        void Affiche();

        void AjouteOption(const Option &);
        void RetireOption(string code);
        float getPrix();
        
        Voiture operator+(Option);
        Voiture operator-(Option);
        Voiture operator-(const string&);

        
    
};
#endif
