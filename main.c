

#include "minish.h"
#include <readline/history.h>
#include <stdio.h>

int main() {

  char *buffer;

  buffer = readline("mokshell->");
  printf("%s\n", buffer);
  free(buffer);
  return 1;
}
