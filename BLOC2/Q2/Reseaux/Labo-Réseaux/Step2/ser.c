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
 int rc ;
 int Desc ;
 struct sockaddr_in sthis ; /* this ce programme */
 struct sockaddr_in sos ; /* s = serveur */
 struct sockaddr_in sor ; /* r = remote */
 
 u_long  IpSocket ;
 u_short PortSocket ;
 
 int tm ;
 struct Requete UneRequete ;
 struct VehiculeHV UnRecord;
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
 
 tm = sizeof(struct Requete) ;
 rc = ReceiveDatagram( Desc,&UneRequete ,tm, &sor ) ; // attend une requete il est bloquant 
 if ( rc == -1 )
    die("ReceiveDatagram") ;
 else
   fprintf(stderr,"bytes recus:%d\n",rc) ;

AfficheRequeteBG(test,UneRequete);
 
 printf("Type recu %d\n", UneRequete.Type) ;
 AfficheRequeteBG(test, UneRequete);
 /* attention l'enum peut être codé en short */
 /* reponse avec psos */
 resuRech=RechercheBG("VehiculesHV",UneRequete.Reference,&UnRecord);
 strcpy(UneRequete.Modele,UnRecord.Modele);
 UneRequete.Quantite=UnRecord.Quantite;
 UneRequete.Cylindree=UnRecord.cylindree;
 strcpy(UneRequete.Constructeur,UnRecord.Constructeur);
 UneRequete.Type = Reponse; 
 //strcat(UneRequete.NomClient," Client") ;



 rc = SendDatagram(Desc,&UneRequete,sizeof(struct Requete) ,&sor ) ;
 if ( rc == -1 )
    die("SendDatagram:") ;
 else
   fprintf(stderr,"bytes envoyes:%d\n",rc ) ;

   fclose(test);
 
 close(Desc) ;
}
