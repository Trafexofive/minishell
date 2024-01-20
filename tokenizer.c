

#include "minish.h"

void *add_token() {}

void *init_prompt(int ac, char **av) {

  char *buffer;

  while (TRUE) {
    buffer = readline("mokshell->");
    parse(buffer);
    free(buffer);
  }
}

// syntax checking
t_oken **tokenize(char *line) {
  t_oken *top;
  char **tokens;
  int i = 0;

  while (line[i]) {
  }
}

t_oken **parse(char *line) {
  t_oken **tokens;

  tokens = tokenize(line);

  printf("%s\n", buffer);
}
