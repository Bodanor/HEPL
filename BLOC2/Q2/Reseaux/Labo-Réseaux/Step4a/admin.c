/******************************************
  Gayet BASTIEN
  2017 Basé sur Fichiers
*******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "LibSerBG.h"
#define BRU (+2)

// include pour les fonctions entrees sortie
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

static struct termios old, new;
 
//clrscr() function definition
// #include <stdlib.h>
void ClrScr(void)
{
    system("clear");
}

void Gotoxy(int x,int y)    
{
    printf("%c[%d;%df",0x1B,y,x);
}

/* Initialize new terminal i/o settings */
 #include <stdio.h>
 #include <stdlib.h>

void initTermios(int echo) 
{
  tcgetattr(0, &old); //grab old terminal i/o settings
  new = old; //make new settings same as old settings
  new.c_lflag &= ~ICANON; //disable buffered i/o
  new.c_lflag &= echo ? ECHO : ~ECHO; //set echo mode
  tcsetattr(0, TCSANOW, &new); //apply terminal io settings
}
 
/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}
 
/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}
 
/* 
Read 1 character without echo 
getch() function definition.
*/
char Getch(void) 
{
  return getch_(0);
}
 
/* 
Read 1 character with echo 
getche() function definition.
*/
char GetchE(void) 
{
  return getch_(1);
}



// permet de supprimer le cr qui placé dans la chaine lors d'un fgets
void DelNewLine(char *Chaine)
{

 Chaine[strlen(Chaine)-1] = 0 ;
}



void MonPrintf(char* tempo, int espace,int taille )
{
 int Count ;
 printf("%s",tempo) ; 
 Count = espace-taille ;
 while ( Count>0 )
 {
       printf(" ");
       Count-- ;
 }
}

void AfficheEnteteVehiculeHV ()
{
 char Tampon[80] ;
 sprintf(Tampon,"%s","Ref" ) ;MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%s","Constructeur") ;    MonPrintf(Tampon,30,strlen(Tampon)) ;
 sprintf(Tampon,"%s","Modele") ;    MonPrintf(Tampon,30,strlen(Tampon)) ;
 sprintf(Tampon,"%s","Quantite") ; MonPrintf(Tampon,6,strlen(Tampon)) ;
 sprintf(Tampon,"%s","Cylindrée "); MonPrintf(Tampon,6,strlen(Tampon)) ;
 printf("\n") ;
}

void AfficheVehiculeHV (struct VehiculeBG   *UnRecord)
{
 char Tampon[80] ;
 sprintf(Tampon,"%d",UnRecord->Reference ) ;  MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%s",UnRecord->Constructeur ) ;    MonPrintf(Tampon,30,strlen(Tampon)) ;
 sprintf(Tampon,"%s",UnRecord->Modele ) ;    MonPrintf(Tampon,30,strlen(Tampon)) ;
 sprintf(Tampon,"%d",UnRecord->Quantite ) ; MonPrintf(Tampon,6,strlen(Tampon)) ;
 sprintf(Tampon,"%d",UnRecord->cylindree) ; MonPrintf(Tampon,6,strlen(Tampon)) ;
 printf("\n") ;
}

void SaiSieVehiculeHV (int Reference, struct VehiculeBG  *UnRecord )
{
 char Tampon[80] ;
 char choix[10] ;
 int test;

 printf("Reference :%d \n",Reference) ;
 UnRecord->Reference = Reference ; 
 printf("Saisie Constructeur :") ;
 fgets(UnRecord->Constructeur ,sizeof UnRecord->Constructeur ,stdin ) ;
 printf("Saisie Modele :") ;
 fgets(UnRecord->Modele ,sizeof UnRecord->Modele ,stdin ) ;
 printf("Saisie Quantite :") ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
 UnRecord -> Quantite = atoi(Tampon) ;

 printf("Pour la cylindrée Tapez 1 pour 1200, Tapez 2 pour 1500 et Tapez 3 pour 2000:");
 fgets(choix,sizeof choix,stdin ) ;
 test = atoi(choix);
 switch (test)
 {
   case 1:
      UnRecord -> cylindree = 1200 ;
   break;
   case 2:
      UnRecord -> cylindree = 1500 ;
   break;

   case 3:
      UnRecord -> cylindree = 2000;
      break;
 }

 
 DelNewLine(UnRecord->Constructeur) ;
 DelNewLine(UnRecord->Modele) ;
 AfficheEnteteVehiculeHV () ;
 AfficheVehiculeHV (UnRecord) ;
 printf("-----------------------\n") ;
 return ;
}

int NombreVehiculesHV (char *NomFichier)
{
 FILE *sortie ;
 sortie = fopen(NomFichier,"r") ; /* Si le fichier existe, on le cree sinon on ajoute */
 if ( sortie == NULL )
    {
     fprintf(stderr,"Pas de fichier\n") ;
     return 0 ;
    }
 else
    fprintf(stderr,"Ouverture reussie \n") ;
 fseek(sortie, 0, SEEK_END ) ;
 return (ftell(sortie)/ sizeof(struct VehiculeBG  )) ;
}

void CreationAjoutVehiculeHV (char *NomFichier,struct VehiculeBG  *UnRecord )
{
 FILE *sortie ;
 char Redo ;
 int nbr ;

 sortie = fopen(NomFichier,"a") ; /* Si le fichier existe, on le cree sinon on ajoute */
 if ( sortie == NULL )
    {
     fprintf(stderr,"Echec Ouverture\n") ;
     exit(0) ;
    }
 else
    fprintf(stderr,"Ouverture reussie \n") ;

 
  printf("Position actuelle dans le fichier %ld\n",ftell(sortie)) ;
  UnRecord-> Supprime = 0 ;
  nbr = fwrite(UnRecord,sizeof(struct VehiculeBG  ),1,sortie) ;

  printf("TAILLE = %ld nbr= %d\n",sizeof(struct VehiculeBG),nbr);

  fflush(sortie) ;
 fclose(sortie) ;
}



void AfficheFacture(struct FactureBG *UneFacture)
{
 char Tampon[80] ;
 struct tm * info ;

 sprintf(Tampon,"%d",UneFacture->NumeroFacturation ) ; MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%s",UneFacture->Acheteur ) ; MonPrintf(Tampon,60,strlen(Tampon)) ;
 info = gmtime(&UneFacture->DateFacturation );
 printf("%2d:%02d' ' ", (info->tm_hour+BRU)%24, info->tm_min);
 //sprintf(Tampon,"%ld",UneFacture->DateFacturation ) ; MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%d",UneFacture->Quantite  ) ; MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%d",UneFacture->Reference) ; MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%d",UneFacture->Cylindree) ; MonPrintf(Tampon,4,strlen(Tampon)) ;

 
 printf("\n") ;
}

void ListingVehiculesHV (char *NomFichier)
{
 struct VehiculeBG   UnRecord ;
 FILE *sortie ;
 char Tampon[80] ;
 int  Numero ;
 int  nbr ;

 sortie = fopen(NomFichier,"r") ; /* Si le fichier existe, on le cree sinon on ajoute */
 if ( sortie == NULL )
    {
     fprintf(stderr,"Echec Ouverture\n") ;
     exit(0) ;
    }
 else
    fprintf(stderr,"Ouverture reussie \n") ;

 AfficheEnteteVehiculeHV () ;
 nbr = fread(&UnRecord,sizeof(UnRecord),1,sortie) ;
 
 while ( !feof(sortie) )
 {
  fprintf(stderr,"Record lu %d et Position actuelle dans le fichier %ld\n",nbr,ftell(sortie)) ;
  AfficheVehiculeHV ( &UnRecord) ;
  nbr = fread(&UnRecord,sizeof(UnRecord),1,sortie) ;
 }
 fclose(sortie) ;
}

void ListingFacturesHV(char *NomFichier)
{
 struct FactureBG UneFacture ;
 FILE *sortie ;
 char Tampon[80] ;
 int  Numero ;
 int  nbr;

 sortie = fopen(NomFichier,"r") ; /* Si le fichier existe, on le cree sinon on ajoute */
 if ( sortie == NULL )
    {
     fprintf(stderr,"Echec Ouverture\n") ;
     exit(0) ;
    }
 else
    fprintf(stderr,"Ouverture reussie \n") ;

 
 nbr = fread(&UneFacture,sizeof(struct FactureBG),1,sortie) ;
 
 while ( !feof(sortie) )
 {
  fprintf(stderr,"Record lu %d et Position actuelle dans le fichier %ld\n",nbr,ftell(sortie)) ;
  AfficheFacture( &UneFacture) ;
  nbr = fread(&UneFacture,sizeof(struct FactureBG ),1,sortie) ;
 }
 fclose(sortie) ;
}


int main()
{
 char Choix ;
 char Tampon[80] ;
 int res ;
 struct VehiculeBG  UnRecord ;
 int Numero ;
 char choix[10];
 int num,ret,quantite,retour;
 time_t rawtime;
 struct tm * info;
 
 
 
 while(1)
 {
  printf("-------2022-----------\n") ;
  printf("1) Ajout              \n") ;
  printf("2) Vehicule           \n") ; 
  printf("4) Recherche          \n") ;   
  printf("5) Achat              \n") ;  
  printf("6) Factures           \n") ;
  printf("7) A propos           \n") ;
  printf("8) exit               \n") ; 
  printf("----------------------\n") ; 
  printf(">>") ; Choix=GetchE() ; printf("\n") ;
  switch(Choix)
  {
   case '1': 
             {
              struct VehiculeBG   UnRecord ;
 	     FILE *sortie ;
             char Redo ;
		
             Redo='y' ;
 	    while ( Redo=='Y' || Redo=='y')
 	    { 
             int Nombre ;
             Nombre= NombreVehiculesHV ("VehiculesBG") ;
  	     SaiSieVehiculeHV (Nombre+1, &UnRecord ) ;
  	     CreationAjoutVehiculeHV ("VehiculesBG",&UnRecord) ; 
  	     printf("Encoder un autre (Y/N) ?)") ;
  	     printf(">>") ; Redo=GetchE() ; printf("\n") ;
 	   }
 
	     break ;	
             }
   case '2': ListingVehiculesHV ("VehiculesBG") ;
             break ;
   case '4': 
   printf("Entrez la reference rechercher : ");
   fgets(choix,sizeof choix,stdin ) ;
   num = atoi(choix);

   ret=RechercheBG("VehiculesBG",num, &UnRecord);
   if(ret==1)
   {
      printf("Trouve");
      AfficheVehiculeHV(&UnRecord);
      
   }
   else
   {
      printf("Pas trouver");
   }
   break;

   case '5' :
            printf("Entrez la reference rechercher : \n");
            fgets(choix,sizeof choix,stdin ) ;
            num = atoi(choix);

            printf("Entrez la quantite voulue : \n");
            fgets(choix,sizeof choix,stdin ) ;
            quantite = atoi(choix);

            ret=RechercheBG("VehiculesBG",num, &UnRecord);
            if(ret==1)
            {
               printf("Trouve");
               AfficheVehiculeHV(&UnRecord);
               
            }
            else
            {
               printf("Pas trouver");
               exit(1);
            }

            ret=ReservationBG("VehiculesBG",num,quantite);

            if(ret>0)
            {
               printf("Reservation reussie\n");
               int date;
               //info(&rawtime);
               //date=info(&rawtime);
               char NomClient[60];
               printf("Entrez votre prenom\n");
               fgets(NomClient,sizeof NomClient,stdin ) ;
               time(&rawtime);
               retour=FacturationBG("FactureBG",NomClient, rawtime , quantite, num,ret);
               if(retour<1)
               {
                  printf("Probleme de facture\n");
               }
               
            }
            else
            {
               if(ret==0)
               {
                  printf("Pas assez de stock \n");
               }
               else
                  printf("Modele non present\n");
            }

             break ;
   case '6': ListingFacturesHV("FactureBG") ;
	     break ;
   case '7': AProposServeurHV("V 1","GAYETBODSON","BastienAlexis") ;
             break ;
   
	
   case '8': exit(0) ; 
  }
 }
}
