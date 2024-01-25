

#ifndef MINISH_H
#define MINISH_H

#include "libft/libft.h"
#include "macros.h"
#include <limits.h>
// #include <readline/history.h>
// #include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_token {
  int data_type;
  char *token;
  struct s_token *next;
  struct s_token *prev;
  bool is_dollar;
  char *expanded_token;
  int quote_type; // 0 - singleq, 1 - dblquote , -1 not quote in token
} t_oken;

typedef struct s_alloc {
  void *address;
  struct s_alloc *next;
} t_alloc;

typedef struct s_info {

  bool in_word;
  bool debug;
  bool flag1;
  bool quote_presence;
  int quote_count;
  int word_start;
  int word_delim;
} t_info;

void *init_prompt(int ac, char **av);
t_oken **parse(const char *line);

#endif
