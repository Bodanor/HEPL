#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"

void AProposServeurHV(char *Version,char *Nom1,char* Nom2) ;
int RechercheBG(char *, int , struct VehiculeBG *);
int ReservationBG(char* NomFichier,int Reference ,int Quantite ) ;
int FacturationBG(char NomFichier[80], char NomClient[60], time_t date,int Quantite,int Reference,int Cylindree) ;

