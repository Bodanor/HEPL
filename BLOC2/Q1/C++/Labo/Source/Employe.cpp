#include "Employe.h"

const string Employe::ADMINISTRATIF = "Administratif";
const string Employe::VENDEUR = "Vendeur";

Employe::Employe() : Intervenant()
{
    #ifdef DEBUG
    cout << "Constructeur par défaut de Employé" << endl;

    #endif

    setLogin("No Login");
    motDePasse = NULL;
    setFonction("Pas de fonction");

}

Employe::Employe(string nom, string prenom, int num, string login_pers, string fonction_pers) : Intervenant(nom, prenom, num)
{
    setFonction(fonction_pers);
    setLogin(login_pers);
    motDePasse = NULL;
}

Employe::Employe(const Employe & src) : Intervenant(src)
{
    setFonction(src.getFonction());
    setLogin(src.getLogin());
    if (src.motDePasse != NULL){
        motDePasse = new string;
        *motDePasse = src.getMotDePasse();
    }
    else
        motDePasse = NULL;

}

Employe::~Employe()
{
    #ifdef DEBUG
        cout << "Deconstructeur de Employe" << endl;
    #endif

    if (motDePasse != NULL)
        delete motDePasse;

    motDePasse = NULL;
}

string Employe::ToString() const
{
    string tmp;
    if (fonction == "Vendeur")
        tmp = "[V";
    else if (fonction == "Administratif")
        tmp = "[A";
    tmp += to_string(getNumero());
    tmp += "]" + getNom() + getPrenom(); 
    return tmp ;

}

string Employe::Tuple() const
{
    string tmp;
    tmp = to_string(getNumero()) + ';';
    tmp += getNom() + ';'  + getPrenom() + ';';
    tmp += getFonction();
    return tmp;

}

void Employe::setFonction(string fonction_employe)
{
    fonction = fonction_employe;
}

void Employe::setLogin(string login_employe)
{
    login = login_employe;
}

void Employe::setMotDePasse(string mdp_employe)
{
    int alpha_flag, digit_flag;
    alpha_flag = digit_flag = 0;

    if (mdp_employe.length() < 6)
        throw(PasswordException("Mot de passe inferieur a 6 cractères", 0));
    
    for (long unsigned int i = 0; i < mdp_employe.length() && (!alpha_flag || !digit_flag); i++){
        if (isalpha(mdp_employe[i]))
            alpha_flag = 1;
        if (isdigit(mdp_employe[i]))
            digit_flag = 1;
    }

    if (!alpha_flag)
        throw(PasswordException("Mot de passe doit contenir au moins une lettre !", 1));
    
    if (!digit_flag)
        throw(PasswordException("Mot de passe doit contenir au moins un chiffre !", 2));
    if (motDePasse != NULL)
        delete motDePasse;
    
    motDePasse = new string;
    *motDePasse = mdp_employe;
    
}

string Employe::getFonction() const
{
    return fonction;
}

string Employe::getLogin() const
{
    return login;
}

string Employe::getMotDePasse() const
{
    if (motDePasse != NULL)
        return *motDePasse;
    else
        return "";
}

void Employe::ResetMotDePasse()
{
    if (motDePasse != NULL)
        delete motDePasse;
    
    motDePasse = NULL   ;

}

Employe& Employe::operator=(const Employe& src)
{
    setLogin(src.getLogin());
    if (src.getMotDePasse() != "")
        setMotDePasse(src.getMotDePasse());
    else
        motDePasse = NULL;
    setFonction(src.getFonction());

    return (*this);
}