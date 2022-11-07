#include "windowclient.h"
#include "ui_windowclient.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

extern WindowClient *w;
void handlerSIgUSR1(int sig);

#include "protocole.h" // contient la cle et la structure d'un message

extern char nomClient[40];
int idQ; // identifiant de la file de message

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
WindowClient::WindowClient(QWidget *parent):QMainWindow(parent),ui(new Ui::WindowClient)
{
  ui->setupUi(this);
  setWindowTitle(nomClient);

  // Recuperation de l'identifiant de la file de messages
  fprintf(stderr,"(CLIENT %s %d) Recuperation de l'id de la file de messages\n",nomClient,getpid());
  // TO DO (etape 2)
  
  if ((idQ = msgget(CLE, 0)) == -1){
      perror("Errur de recuperatoin de la cle");
      exit(1);
  }

  MESSAGE id;

  id.type = 1;
  id.expediteur = getpid();
  strcpy(id.texte, nomClient);

  if (msgsnd(idQ, &id, sizeof(MESSAGE)-sizeof(long), 0) == -1){
    perror("Impossible de s'identifier au près du serveur !\n");
    exit(1);
  }

  struct sigaction sigusr1;
  sigusr1.sa_flags = 0;
  sigusr1.sa_handler = handlerSIgUSR1;
  sigemptyset(&sigusr1.sa_mask);
  sigaction(SIGUSR1, &sigusr1, NULL);

}

WindowClient::~WindowClient()
{
  delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setRecu(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditRecu->clear();
    return;
  }
  ui->lineEditRecu->setText(Text);
}

void WindowClient::setAEnvoyer(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditEnvoyer->clear();
    return;
  }
  ui->lineEditEnvoyer->setText(Text);
}

const char* WindowClient::getAEnvoyer()
{
  if (ui->lineEditEnvoyer->text().size())
  { 
    strcpy(aEnvoyer,ui->lineEditEnvoyer->text().toStdString().c_str());
    return aEnvoyer;
  }
  return NULL;
}

const char* WindowClient::getRecu()
{
  if (ui->lineEditRecu->text().size())
  { 
    strcpy(recu,ui->lineEditRecu->text().toStdString().c_str());
    return recu;
  }
  return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::on_pushButtonEnvoyer_clicked()
{
    MESSAGE msg;

    fprintf(stderr,"Clic sur le bouton Envoyer\n");

    msg.type = 1;
    strcpy(msg.texte, getAEnvoyer());
    msg.expediteur = getpid();

    if (msgsnd(idQ, &msg, sizeof(MESSAGE) - sizeof(long), 0) == -1){
        perror("Erreur de msgsend");
        exit(1);
    }

}

void WindowClient::on_pushButtonQuitter_clicked()
{
  fprintf(stderr,"Clic sur le bouton Quitter\n");
  exit(1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Handlers de signaux ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TO DO (etape 4)

void handlerSIgUSR1(int sig)
{
  MESSAGE rcv;
  printf("Recu du signal SIGUSR1...\n");
  if (msgrcv(idQ, &rcv, sizeof(MESSAGE) - sizeof(long), getpid(), 0) == -1){
    perror("Erreur de msgrecv !");
    exit(1);
  }
  else
    w->setRecu(rcv.texte);


}