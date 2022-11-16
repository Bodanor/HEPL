#ifndef __EMPLOYE_H__
#define __EMPLOYE_H__

#include <iostream>
#include <string>

#include "Intervenant.h"
#include "PasswordException.h"

using namespace std;


class Employe : public Intervenant
{
    private:
        string login;
        string *motDePasse;
        string fonction;
    
    public:
        Employe();
        Employe(string, string , int, string, string);
        Employe(const Employe&);
        ~Employe();

        string ToString() const;
        string Tuple() const;


        void setFonction(string);
        void setLogin(string);
        void setMotDePasse(string);

        string getFonction() const;
        string getLogin() const;
        string getMotDePasse() const;
        void ResetMotDePasse();

        Employe& operator=(const Employe&);
        static const string ADMINISTRATIF;
        static const string VENDEUR;
        static const int INVALID_LENGHT;
        static const int ALPHA_MISSING;
        static const int DIGIT_MISSING;
        static const int NO_PASSWORD;

};
#endif