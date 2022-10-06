#include "Option.h"

using namespace std;

Option::Option()
{
    #ifdef DEBUG
        cout << "Constructeur par défaut d'Option" << endl;
    #endif

    code = "";
    intitule = "";
    prix = 0.0f;
    
}

Option::Option(string code_opt, string intitule_opt, float prix_opt)
{
    #ifdef DEBUG
        cout << "Constructeur par initialisation d'Option" << endl;
    #endif
    
    code = code_opt;
    intitule = intitule_opt;
    prix = prix_opt;
}

Option::Option(const Option &opt)
{
    #ifdef DEBUG
        cout << "Constructeur de copie d'Option" << endl;
    #endif
    
    setCode(opt.getCode());
    setIntitule(opt.getIntitule());
    setPrix(opt.getPrix());
}

Option::~Option()
{
    #ifdef DEBUG
        cout << "Deconstructeur d'Option" << endl;
    #endif
}

string Option::getCode() const
{
    return code;
}

string Option::getIntitule() const
{
    return intitule;
}

float Option::getPrix() const
{
    return prix;
}

void Option::setPrix(float prix_opt)
{
    if (prix >= 0)
        prix = prix_opt;
}

void Option::setIntitule(string intitule_opt)
{
    intitule = intitule_opt;
}

void Option::setCode(string code_opt)
{
    code = code_opt;
}

void Option::Affiche() const
{
    cout << "Code : " << code << endl;
    cout << "Intitule : " << intitule << endl;
    cout << "Prix de l'option : " << prix << endl;

}
