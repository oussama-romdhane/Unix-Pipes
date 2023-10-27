#include "serv_cli_fifo.h"

int main() {
  unlink(FIFO1);
  unlink(FIFO2);
  return 0;
}
