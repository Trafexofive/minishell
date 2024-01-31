

#ifndef MINISH_H
#define MINISH_H

#include "../libft/libft.h"
#include "macros.h"
#include <limits.h>
// #include <readline/history.h>
// #include <readline/readline.h>
#include "garbage.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_token {
  int data_type;
  char *token;
  struct s_token *next;
  struct s_token *prev;
  bool is_dollar;
  char *expanded_token; // good idea but expanding should be after the parser is
                        // done
  int quote_type;       // 0 - singleq, 1 - dblquote , -1 not quote in token
} t_oken;

typedef struct s_cmd {
  struct s_token *tokens;
} t_cmd;
typedef struct s_info {

  t_alloc *alloc_head;
  char *line;
  bool debug;
  int cursor;
  bool quote_presence;
  int quote_count;
  int word_start;
  int word_delim;
  struct s_token *head;
} t_info;

#endif
