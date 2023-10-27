#ifndef SERV_CLI_FIFO_H
#define SERV_CLI_FIFO_H

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define NMAX 100      // You can set NMAX to your desired maximum value.
#define FIFO1 "fifo1" // Name of the first FIFO (server waiting for questions).
#define FIFO2 "fifo2" // Name of the second FIFO (server sending answers).

// Define a structure for a question from the client.
typedef struct {
  int client_id;       // Client's unique identifier.
  int num_to_generate; // Number of random values to generate.
} Question;

// Define a structure for an answer from the server.
typedef struct {
  int client_id;              // Client's unique identifier.
  int server_id;              // Client's unique identifier.
  int generated_values[NMAX]; // Array to hold generated random values.
  int num_generated;          // Number of values generated.
} Answer;

#endif // SERV_CLI_FIFO_H
