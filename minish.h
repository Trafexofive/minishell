

#ifndef MINISH_H
#define MINISH_H

#include "libft/libft.h"
#include "macros.h"
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_token {
  unsigned int data_type;
  char *token;
  struct s_token *next;
  struct s_token *prev;
} t_oken;

void *init_prompt(int ac, char **av);

#endif
