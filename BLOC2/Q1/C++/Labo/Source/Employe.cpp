#include "Employe.h"

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

Employe::Employe(const Employe & src) : Intervenant(src.getNom(), src.getPrenom(), src.getNumero())
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