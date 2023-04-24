#ifndef __PERSONNE_H__
#define __PERSONNE_H__

#include <iostream>
#include <string>

using namespace std;

class Personne
{
    friend ostream& operator<<(ostream&, const Personne &);
    friend istream& operator>>(istream&, Personne&);

    protected:
        string nom;
        string prenom;
    
    public:
        Personne();
        Personne(const string, const string);
        Personne(const Personne &);
        ~Personne();

        void setNom(string nom);
        void setPrenom(string nom);
        string getPrenom() const;
        string getNom() const;
        void Affiche() const;
        Personne& operator=(const Personne&);
};

#endif