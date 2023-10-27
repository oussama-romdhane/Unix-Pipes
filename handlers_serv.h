#ifndef HANDLERS_SERV_H
#define HANDLERS_SERV_H

#include "serv_cli_fifo.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// Handler for server wake-up signal SIGUSR1.
void hand_reveil(int sig) {
  // Implement your wake-up logic here.
  printf("Le Client a Recu La Reponse!\n");
  // For example, you can use a flag or other mechanism to indicate the server
  // to send the answer.
}

// Handler for server termination on receiving any signal.
void fin_serveur(int sig) {
  printf("Aucun Client Connecté!\n");
  printf("Supression des Pipes...\n");
  unlink(FIFO1);
  unlink(FIFO2);
  printf("Fermeture du Serveur...\n");
  exit(0);
}

#endif // HANDLERS_SERV_H
