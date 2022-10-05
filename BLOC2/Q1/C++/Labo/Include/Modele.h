#ifndef MODELE_H
#define MODELE_H

enum Moteur { Essence, Diesel, Electrique, Hybride };

class Modele   
{
    private : 
        char * nom;
        int puissance;
        Moteur moteur;
        float prix;

    public : 
        Modele();
        Modele(const char *, int, Moteur, float);
        Modele(const Modele &);
        ~Modele();
        
        void operator=(Modele modele);
        const char * getNom()const;//"return de la variable"
        int getPuissance()const;
        Moteur getMoteur()const;
        float getPrixDeBase()const;

        void setNom(const char *);
        void setPuissance(int);
        void setMoteur(Moteur);
        void setPrixDeBase(float);
        
        void Affiche()const;//Ne modfifie pas les variables membres
};


#endif
