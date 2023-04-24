/*--------------------------------------
  GAYET BASTIEN
  
  ex02\ser.c 
  
  Un serveur recevant une structure 
----------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "../udplib/udplib.h"
#include "RequeteBG.h"
#include "data.h"
#include "LibSerBG.h"


void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc,char *argv[])
{
 int rc, res;
 int Desc ;
 struct sockaddr_in sthis ; /* this ce programme */
 struct sockaddr_in sos ; /* s = serveur */
 struct sockaddr_in sor ; /* r = remote */
 
 u_long  IpSocket ;
 u_short PortSocket ;
 
 int tm ;
 struct Requete UneRequete ;
 struct VehiculeBG UnRecord;
 int resuRech;

 memset(&sthis,0,sizeof(struct sockaddr_in)) ;
 memset(&sos,0,sizeof(struct sockaddr_in)) ; 
 memset(&sor,0,sizeof(struct sockaddr_in)) ; 
 
 printf("Ceci est le serveur\n") ;
 if ( argc!=3)
 {
  printf("ser ser port cli\n") ;
  exit(1) ;
 }
   FILE * test;

   test=fopen("LogSer","a");
   if(test ==NULL)
   {
      fprintf(stderr,"Echec Ouverture\n");
      exit(0);
   }
   else
   {
      fprintf(stderr,"Ouverture reussie\n");
   }
 
 /* Récupération IP & port   */
 IpSocket= inet_addr(argv[1]);
 PortSocket = atoi(argv[2]);
 // Desc = CreateSockets(&psoo,&psos,,atoi(argv[2]),argv[3],atoi(argv[4])) ;
 Desc=creer_socket(SOCK_DGRAM,&IpSocket,PortSocket,&sthis);
 
 if ( Desc == -1 )
    die("CreateSockets:") ;
 else
    fprintf(stderr,"CreateSockets %d\n",Desc) ;
 while (1)
 {
   
 tm = sizeof(struct Requete) ;
 rc = ReceiveDatagram( Desc,&UneRequete ,tm, &sor ) ; // attend une requete il est bloquant 
 if ( rc == -1 )
    die("ReceiveDatagram") ;
 else
   fprintf(stderr,"bytes recus:%d\n",rc) ;

   AfficheRequeteBG(test,UneRequete);
    // Le traitement doit être s&paré des requetes réseaux */
   printf("Received packet from %s:%d\n", inet_ntoa(sor.sin_addr), ntohs(sor.sin_port));
   fprintf(stderr,"Received packet from %s:%d\n", inet_ntoa(sor.sin_addr), ntohs(sor.sin_port));
 switch (UneRequete.Type)
 {
 case Question:
    resuRech=RechercheBG("VehiculesBG",UneRequete.Reference,&UnRecord);
    fprintf(stderr,"res :%d Reference:%d  Modele : %s  Cylindree : %d\n",res,UnRecord.Reference, UnRecord.Modele, UnRecord.cylindree) ;

     memset(&UneRequete,0, sizeof(struct Requete)) ;
   
   
      UneRequete.Reference = UnRecord.Reference ; 
      strncpy(UneRequete.Constructeur,UnRecord.Constructeur,sizeof(UneRequete.Constructeur)) ;
      strncpy(UneRequete.Modele,UnRecord.Modele,sizeof(UneRequete.Modele)) ;
      UneRequete.Quantite=UnRecord.Quantite;
      UneRequete.Cylindree=UnRecord.cylindree;
   
   break;
 }
 printf("Type recu %d\n", UneRequete.Type) ;
 AfficheRequeteBG(test, UneRequete);
 /* attention l'enum peut être codé en short */
 /* reponse avec psos */

 UneRequete.Type = Reponse; 
 //strcat(UneRequete.NomClient," Client") ;



 rc = SendDatagram(Desc,&UneRequete,sizeof(struct Requete) ,&sor ) ;
 if ( rc == -1 )
    die("SendDatagram:") ;
 else
   fprintf(stderr,"bytes envoyes:%d\n",rc ) ;

   fclose(test);
} 
 close(Desc) ;
}
