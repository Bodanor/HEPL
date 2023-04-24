
enum TypeRequete {
       Question = 1 ,
       Reponse = 2
       /*Achat = 2 ,
       Livraison = 3,
       Ok = 4 ,
       Fail = 5*/
     } ;

struct Requete
{
  enum TypeRequete Type ;
  int Numero ; // Contient le numéro de la requete
  int NumeroFacture ;
  time_t Date ; 
  int Reference ;
  int Quantite ;
  int Prix ;
  int Cylindree ; 
  char Constructeur[30] ;
  char Modele[30] ;
  char NomClient[80] ;
  
} ; 

#include <stdio.h>

void AfficheRequeteBG(FILE *fp, struct Requete R )
{
fprintf(fp,">TypeRequete %d \n", R.Type ) ;
fprintf(fp," Reference %d \n", R.Numero ) ;
fprintf(fp," NumeroFacture %d \n", R.NumeroFacture ) ;
fprintf(fp," Date %ld \n", R.Date ) ;
fprintf(fp," Reference %d \n", R.Reference ) ;
fprintf(fp," Places %d \n", R.Quantite ) ;
fprintf(fp," Prix %d \n", R.Prix ) ;
fprintf(fp,"Cylindree %d \n", R.Cylindree) ;
fprintf(fp,"Constructeur %s \n", R.Constructeur ) ;
fprintf(fp,"Modele %s \n", R.Modele ) ;
fprintf(fp," Client %s \n\n", R.NomClient ) ;
return ;
}

