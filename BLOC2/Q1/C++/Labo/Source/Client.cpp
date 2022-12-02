#include "Client.h"


Client::Client() : Intervenant()
{
    #ifdef DEBUG
    cout << "Constructeur par défaut de Client" << endl;

    #endif
    setNumero(0);
    setGsm("");
}

Client::Client(const string nom_client, const string prenom_client, int num_client, const string gsm_client) : Intervenant(nom_client,  prenom_client, num_client)
{
    setGsm(gsm_client);
}

Client::Client(const Client & src) : Intervenant(src.getNom(), src.getPrenom(), src.getNumero())
{
    setGsm(src.getGsm());
}

Client::~Client()
{
    #ifdef DEBUG
        cout << "Deconstructeur de Client" << endl;
    #endif
}

int Client::cmpClient(const Client& src)
{
    if (nom < src.nom)
        return -1;
    if (nom > src.nom)
        return 1;
    if (prenom < src.prenom)
        return -1;
    if (prenom > src.prenom)
        return 1;
    else
        return 0;
}

int Client::operator<(const Client & src)
{
    return cmpClient(src) == -1;
}

int Client::operator>(const Client & src)
{
    return cmpClient(src) == 1;
}

int Client::operator==(const Client & src)
{
    return cmpClient(src) == 0;
}

int Client::getNumero() const
{
    return numero;

}

string Client::getGsm() const
{
    return gsm;
}

void Client::setGsm(string num_gsm)
{
    gsm = num_gsm;
}

void Client::setNumero(int num_client)
{
    numero = num_client;
}

Client & Client::operator=(const Client& src)
{
    setPrenom(src.getPrenom());
    setNom(src.getNom());
    setNumero(src.getNumero());
    setGsm(src.getGsm());

    return (*this);
}

string Client::ToString() const
{
    string tmp;
    tmp = "[C" + to_string(getNumero());
    tmp += "]" + getNom() + getPrenom(); 
    return tmp ;
}

string Client::Tuple() const    
{
    string tmp;
    tmp = to_string(getNumero()) + ';';
    tmp += getNom() + ';'  + getPrenom() + ';';
    tmp += getGsm();
    return tmp;
}