#ifndef HANDLERS_SERV_H
#define HANDLERS_SERV_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// Handler for server wake-up signal SIGUSR1.
void hand_reveil(int sig) {
  // Implement your wake-up logic here.
  printf("Server Received Signal\n");
  // For example, you can use a flag or other mechanism to indicate the server
  // to send the answer.
}

// Handler for server termination on receiving any signal.
void fin_serveur(int sig) {
  // Implement server termination logic here.
  // You can perform cleanup and exit gracefully.
}

#endif // HANDLERS_SERV_H
