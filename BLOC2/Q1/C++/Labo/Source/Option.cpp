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
    
    setCode(code_opt);
    setIntitule(intitule_opt);
    setPrix(prix_opt);
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
    if (prix_opt >= 0)
        prix = prix_opt;
    else
        throw(OptionException("Le prix doit être positif !"));
}

void Option::setIntitule(string intitule_opt)
{
    if (intitule_opt == "")
        throw(OptionException("L'intitule est vide !"));
    else
        intitule = intitule_opt;
}

void Option::setCode(string code_opt)
{
    if (code_opt == "")
        throw(OptionException("Code vide !"));
    
    if (code_opt.length() > 4)
        throw(OptionException("Code fait plus de 4 carcatères !"));
    code = code_opt;
}

void Option::Affiche() const
{
    cout << "Code : " << code << endl;
    cout << "Intitule : " << intitule << endl;
    cout << "Prix de l'option : " << prix << endl;

}

ostream& operator<<(ostream& s, const Option& opt)
{
    s << "Code : " << opt.code << endl;
    s << "Intitule : " << opt.intitule << endl;
    s << "Prix de l'option : " << opt.prix << endl;

    return s;
}
istream& operator>>(istream& s, Option& opt)
{
    float prix;
    string tmp;

    cout << "Code : ";
    getline(s, tmp);
    opt.setCode(tmp);
    cout << "Intitule : ";
    getline(s, tmp);
    opt.setIntitule(tmp);
    cout << "Prix : ";
    s >> prix;
    opt.setPrix(prix);

    s.ignore();

    return s;
}

void Option::operator=(Option opt)
{
    code = opt.getCode();
    intitule = opt.getIntitule();
    prix = opt.getPrix();
}
Option Option::operator--(int) 
{
    Option tmp(*this);
    setPrix(prix - 50);

    return tmp;

}

Option Option::operator--() 
{
    setPrix(prix - 50);
    return (*this);
}

void Option::Save(ostream &fichier) const
{
	int size_tmp;
	

	if (!fichier)
		cout << "Impossible de sauvegarder l'option !" << endl;

	else {
        
		size_tmp = code.size();
		fichier.write((char*)&size_tmp, sizeof(size_tmp));
		fichier.write((char*)code.data(), size_tmp*sizeof(char));

        size_tmp = intitule.size();
		fichier.write((char*)&size_tmp, sizeof(size_tmp));
		fichier.write((char*)intitule.data(), size_tmp*sizeof(char));

		fichier.write((char*)&prix, sizeof(prix));
	}
    
}

void Option::Load(istream &fichier)
{
	int size_tmp = 0;

	if (!fichier)
		cout << "Impossible de lire l'option !" << endl;

	else {
		fichier.read((char*)&size_tmp, sizeof(int));
		code.resize(size_tmp);
		fichier.read((char*)code.data(), size_tmp*sizeof(char));
		code.append("\0");
		
		fichier.read((char*)&size_tmp, sizeof(size_tmp));
		intitule.resize(size_tmp);
		fichier.read((char*)intitule.data(), size_tmp*sizeof(char));
		intitule.append("\0");

		fichier.read((char*)&prix, sizeof(prix)); 
	}
	
}
