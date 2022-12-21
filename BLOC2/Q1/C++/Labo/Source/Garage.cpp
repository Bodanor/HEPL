#include "Garage.h"


Garage::Garage()
{
	#ifdef DEBUG
	cout << "Contructeur par default de GARAGE" << endl;
	#endif
}

void Garage::ajouteModele(const Modele &m)
{
	modeles.insere(m);

}

void Garage::afficheModelesDisponibles() const
{
	modeles.Affiche();
}

Modele Garage::getModele(int indice)
{
	return modeles[indice];
}

void Garage::ajouteOption(const Option &o)
{
	options.insere(o);

}

void Garage::afficheOptionsDisponibles() const
{
	options.Affiche();
}

Option Garage::getOption(int indice)
{
	return options[indice];
}

void Garage::ajouteClient(string nom, string prenom, string gsm)
{
	Client tmp(nom, prenom, Intervenant::numCourant, gsm);
	clients.insere(tmp);
	Intervenant::numCourant++;
}

void Garage::afficheClients() const
{
	clients.Affiche();
}
void Garage::supprimeClientParIndice(int ind)
{
	clients.retire(ind);
}

void Garage::supprimeClientParNumero(int num)
{
	for (int i = 0; i < clients.size(); i++) {
		if (clients[i].getNumero() == num) {
			clients.retire(i);
		}
	}
}

void Garage::ajouteEmploye(string nom,string prenom,string login,string fonction)
{
	Employe tmp(nom, prenom, Intervenant::numCourant, login, fonction);
	employes.insere(tmp);
	Intervenant::numCourant++;
}

void Garage::afficheEmployes() const
{
	employes.Affiche();
}

void Garage::supprimeEmployeParIndice(int ind)
{
	employes.retire(ind);
}

void Garage::supprimeEmployeParNumero(int num)
{
	for (int i = 0; i < employes.size(); i++) {
		if (employes[i].getNumero() == num) {
			employes.retire(i);
		}
	}

}