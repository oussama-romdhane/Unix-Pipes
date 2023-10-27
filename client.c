#include "handlers_cli.h"
#include "serv_cli_fifo.h"

int main() {
  /* Declarations */
  int fifo1_fd, fifo2_fd; // File descriptors for the FIFOs
  Question question;
  Answer answer;
  int server_id;

  printf("Sup Sup:\n");

  /* Open the named pipes (FIFOs) */
  fifo1_fd = open(FIFO1, O_WRONLY);
  fifo2_fd = open(FIFO2, O_RDONLY);

  int num_to_generate = 0;
  while (num_to_generate < 1 || num_to_generate > NMAX) {
    printf("Veuillez introduire un nombre: ");
    scanf("%d", &num_to_generate);

    if (num_to_generate < 1 || num_to_generate > NMAX) {
      printf("Nombre Invalide, veuillez introduire un nombre positif inférieur "
             "a %d\n",
             NMAX);
    }
  }

  /* Install signal handler for wake-up (SIGUSR1) */
  signal(SIGUSR1, hand_reveil);

  /* Construct and send a question */
  question.client_id =
      getpid(); // You can use a unique identifier for the client.

  question.num_to_generate = num_to_generate;

  if (write(fifo1_fd, &question, sizeof(Question)) < 0) {
    perror("write FIFO1");
    exit(1);
  }

  printf("Answer Sent:\n");

  pause();

  /* Read the response */
  if (read(fifo2_fd, &answer, sizeof(Answer)) < 0) {
    perror("read FIFO2");
    exit(1);
  }

  printf("Answer ID: %d\n", answer.client_id);
  printf("Answer Number: %d\n", answer.num_generated);
  for (int i = 0; i < answer.num_generated; i++) {
    printf("%d ", answer.generated_values[i]);
  }

  server_id = answer.server_id;

  /* Send the SIGUSR1 signal to the server to notify it that
   * you've read the response */
  kill(server_id, SIGUSR1);

  /* Local processing of the response */
  // You can add code here to handle the received answer as needed.

  return 0;
}
