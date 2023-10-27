#ifndef HANDLERS_CLI_H
#define HANDLERS_CLI_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// Handler for client wake-up signal SIGUSR1.
void hand_reveil(int sig) {
  // Implement your wake-up logic here.
  // For example, you can use a flag or other mechanism to handle the wake-up.
    printf("Client Received Signal\n");

}

#endif // HANDLERS_CLI_H
