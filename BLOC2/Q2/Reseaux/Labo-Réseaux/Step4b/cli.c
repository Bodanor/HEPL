/*---------------------------------------------------------------
   Gayet Bastien
   ex02\cli.c

 Le client dit bonjour en utilisant un structure  et
 le serveur fait de même
------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "../udplib/udplib.h"
#include "RequeteBG.h"
#include "LibSerBG.h"

void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char *argv[])
{
 int rc ;
 int Desc ;
 int tm ; 
 int ref;
 char NomClient[60];

  FILE *sortie ;

 sortie = fopen("LogCli","a") ; /* Si le fichier existe, on le cree sinon on ajoute */
 if ( sortie == NULL )
 {
  fprintf(stderr,"Echec Ouverture\n") ;
  exit(0) ;
 }
 else
    fprintf(stderr,"Ouverture reussie \n") ;
 
 u_long  IpSocket , IpServer;
 u_short PortSocket, PortServer ; 
 
 struct sockaddr_in sthis ; /* this ce programme */
 struct sockaddr_in sos ; /* s = serveur */
 struct sockaddr_in sor ; /* r = remote */
 struct Requete UneRequete;

 memset(&sthis,0,sizeof(struct sockaddr_in)) ;
 memset(&sos,0,sizeof(struct sockaddr_in)) ; 
 memset(&sor,0,sizeof(struct sockaddr_in)) ; 
 
 if (argc!=5)
  
{
    printf("cli client portc serveur ports\n") ;
    exit(1) ;
 }
 
 /* Récupération IP & port   */
 IpSocket= inet_addr(argv[1]);
 PortSocket = atoi(argv[2]);
 
 IpServer = inet_addr(argv[3]) ;
 PortServer = atoi(argv[4]);
 
 // Desc = CreateSockets(&psoo,&psos,,atoi(argv[2]),argv[3],atoi(argv[4])) ;
 Desc=creer_socket(SOCK_DGRAM,&IpSocket,PortSocket,&sthis);
 
 if ( Desc == -1 )
    die("CreateSockets:") ; 
 else
    fprintf(stderr,"CreateSockets %d\n",Desc) ;
 
  sos.sin_family = AF_INET ;
  sos.sin_addr.s_addr= IpServer ;
  sos.sin_port = htons(PortServer) ;


 char choix;
  do
{
    printf("Menu:\n");
    printf("1. Reference\n");
    printf("2. Achat vehicule\n");
    printf("3. Quitter\n");
    printf("Veuillez entrer votre choix: ");
    scanf("%d", &ref);

    switch(ref)
    {
        case 1:
            printf("Vous avez choisi la reference\n");

            printf("Entrez la reference rechercher :");
            scanf("%d",&UneRequete.Reference);
            strcpy(UneRequete.NomClient, "");
            UneRequete.Type = Question ; 
            break;
        case 2:
            
         printf("Entrez Nom\n");
         scanf("%s",NomClient);
         strcpy(UneRequete.NomClient,NomClient);

         printf("Entrez la reference rechercher :");
         scanf("%d",&UneRequete.Reference);

         printf("Entre quantite : \n");
         scanf("%d",&UneRequete.Quantite);

         time_t rawtime;
         struct tm * info;
         time(&rawtime);
         UneRequete.Date=rawtime;
         UneRequete.Type=Achat;

         break;

        case 3:
            printf("Vous avez choisi de quitter\n");
            break;

    }

    printf("Voulez-vous continuer? (O/N) ");
    scanf(" %c", &choix);
} while(choix == 'O' || choix == 'o');

 
 /*strncpy(UneRequete.Message , "Avec une structure: Bonjour" , sizeof(UneRequete.Message)) ;*/
 
   AfficheRequeteBG(sortie,UneRequete);
 rc = SendDatagram(Desc,&UneRequete,sizeof(struct Requete) ,&sos ) ; // envoi requete 

 

 if ( rc == -1 )
    die("SendDatagram") ;
 else
   fprintf(stderr,"Envoi de %d bytes\n",rc ) ;
 
 memset(&UneRequete,0,sizeof(struct Requete)) ;
 tm = sizeof(struct Requete) ;
 
  rc = ReceiveDatagram( Desc, &UneRequete,tm, &sor ) ; if ( rc == -1 )
    die("ReceiveDatagram") ;
 else
   fprintf(stderr,"bytes recus:%d\n",rc) ;


   printf("Achat reussi facture %d",UneRequete.NumeroFacture);
   //fprintf(stderr," Ref : %d, Modele : %s ,  Cylindree  %d \n",UneRequete.Reference, UneRequete.Modele, UneRequete.Cylindree);
   

   fclose(sortie);
   close(Desc) ;
}
