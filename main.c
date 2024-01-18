

#include "minish.h"

int main() {

  char *buffer;

  buffer = readline("mokshell->");
  printf("%s\n", buffer);
  free(buffer);
  return 1;
}
