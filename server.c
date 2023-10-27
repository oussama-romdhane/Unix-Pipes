#include "handlers_serv.h"
#include "serv_cli_fifo.h"

int main() {
  /* Declarations */
  int fifo1_fd, fifo2_fd; // File descriptors for the FIFOs
  Question question;
  Answer answer;
  int server_id = getpid();

  /* Create named pipes (FIFOs) if they don't exist */
  if (mkfifo(FIFO1, 0666) == -1) {
    perror("mkfifo FIFO1");
    exit(1);
  }
  if (mkfifo(FIFO2, 0666) == -1) {
    perror("mkfifo FIFO2");
    exit(1);
  }

  printf("Created Pipes:\n");

  /* Initialize the random number generator */
  srand(getpid());

  /* Open the named pipes */
  fifo1_fd = open(FIFO1, O_RDONLY);
  fifo2_fd = open(FIFO2, O_WRONLY);

  printf("Opened Pipes:\n");

  /* Install signal handlers */
  signal(SIGUSR1, hand_reveil);
  // You may want to install a signal handler for other signals as well if
  // needed.

  while (1) {
    printf("Reading Questions...\n");
    /* Read a question from the client */
    if (read(fifo1_fd, &question, sizeof(Question)) < 0) {
      perror("read FIFO1");
      continue;
    }

    printf("Client ID: %d\n", question.client_id);
    printf("Client Question: %d\n", question.num_to_generate);

    /* Construct the response */
    answer.server_id = server_id;
    answer.client_id = question.client_id;
    answer.num_generated = 0;

    for (int i = 0; i < question.num_to_generate; i++) {
      answer.generated_values[i] = rand() % NMAX;
      answer.num_generated++;
    }

    /* Send the response to the client */
    if (write(fifo2_fd, &answer, sizeof(Answer)) < 0) {
      perror("write FIFO2");
      continue;
    }

    /* Send the SIGUSR1 signal to the client to notify it */
    kill(question.client_id, SIGUSR1);
    pause();
    printf("Client Received Response\n");
  }

  /* Cleanup and close the pipes if necessary */
  unlink(FIFO1);
  unlink(FIFO2);

  return 0;
}
