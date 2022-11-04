#include <cstdlib>
#include <locale>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <string.h>
#include "protocole.h" // contient la cle et la structure d'un message

int idQ;
int pid1,pid2;

int main()
{
  MESSAGE requete;
  pid_t destinataire;

  // Armement du signal SIGINT
  // TO DO (etape 6)
  // Creation de la file de message
  // Si la file existe ne pas la recrée

  fprintf(stderr,"(SERVEUR) Creation de la file de messages\n");
  if ((idQ = msgget(CLE, IPC_CREAT | 0600)) == -1){
      perror("Erreur de msgget");
      exit(1);
  }
  // Attente de connection de 2 clients
  fprintf(stderr,"(SERVEUR) Attente de connection d'un premier client...\n");
  if (msgrcv(idQ, &requete, sizeof(MESSAGE)-sizeof(long), 1, 0) == -1){
    perror("Impossible d'obtenir le PID du client 1 !\n");
    exit(1);
  }
  else{
    pid1 = requete.expediteur;
    fprintf(stderr, "Client %s (%d) connecte \n",requete.texte, requete.expediteur);
  }

  fprintf(stderr,"(SERVEUR) Attente de connection d'un second client...\n");
  if (msgrcv(idQ, &requete, sizeof(MESSAGE)-sizeof(long), 1, 0) == -1){
    perror("Impossible d'obtenir le PID du client 2 !\n");
    exit(1);
  }
  else{
    pid2 = requete.expediteur;
    fprintf(stderr, "Client %s (%d) connecte \n", requete.texte, requete.expediteur);
  }

  while(1) 
  {
    char tmp[80];

  	fprintf(stderr,"(SERVEUR) Attente d'une requete...\n");
    if (msgrcv(idQ, &requete, sizeof(MESSAGE)-sizeof(long),1, 0) == -1){
        perror("Errreur de msgrcv !");
        exit(1);
    }
    fprintf(stderr,"(SERVEUR) Requete recue de %d : --%s--\n",requete.expediteur,requete.texte);
    
    destinataire = requete.expediteur;

    /* Inclure la signature du serveur en utilisant un buffer */
    requete.expediteur = 1;
    strcpy(tmp, requete.texte);
    strcpy(requete.texte, "(SERVEUR)");
    strcat(requete.texte, tmp);

    requete.type = (destinataire == pid1) ? pid2 : pid1;
    destinataire = (destinataire == pid1) ? pid2 : pid1;

    requete.expediteur = 1;

    fprintf(stderr,"(SERVEUR) Envoi de la reponse a %d\n",destinataire);
    if (msgsnd(idQ, &requete, sizeof(MESSAGE)-sizeof(long),0) == -1){
        perror("Erreur de msgsnd");
    }

    kill(destinataire, SIGUSR1);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Handlers de signaux ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TO DO (etape 6)
