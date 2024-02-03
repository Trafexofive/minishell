

#ifndef MINISH_H
#define MINISH_H

#include "../libft/libft.h"
#include "garbage.h"
#include "macros.h"
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

// typedef enum s_cmd_type
// {
// 	WORD = 1;
// 	PIPE = 2;
// 	AMPERS = 3;
// 	REDIR = 4;
// 	OR = 5;
// 	DOLLAR = 6;

// } t_cmd_type;

typedef struct s_token {
  int data_type;
  char *token;
  struct s_token *next;
  struct s_token *prev;
  bool dollar_presence;
  bool  join_next; // words should also be joined if they connect with a quote.
                        // done
  int quote_type;       // 0 - singleq, 1 - dblquote , -1 not quote in token
} t_oken;

typedef struct s_lex {
  bool flag;
} t_lex;

typedef struct s_cmd {
  struct s_token *tokens;
  char **cmd;
  struct s_cmd *next;
  struct s_cmd *prev;
  struct s_redir *redir; // if not redir set to NULL
  struct s_redir *redir_out;
  int status;
  int pid;
} t_cmd;

typedef struct s_redir {
  int type;
  char *file;
  struct s_redir *next;
  } t_redir;
  

typedef struct s_info {
  t_alloc *alloc_head;
  t_cmd *cmd;
  char *line;
  int cursor;
  struct s_token *pipe;
  struct s_token *head;
} t_info;


void	parse_error(const char *exit_msg, t_info *info);
void	print_arr(char **str);
bool	is_space(char c);
int	quote_len(char *line, t_info *info);
bool	is_operator(char c);
bool	is_quote(char c);
int	last_char_in_word(char *line, t_info *info);
void	print_tokens(t_oken *head);
void	handle_operator(char *line, t_info *info);
t_oken *handle_word(char *line, t_info *info);
void	handle_dollar(char *line, t_info *info);
t_info	*main_loop(char *line, t_info *info);
bool	check_line(char *line, t_info *info);
int	word_len(t_info *info);
bool	valid_quotes(t_info *info);
bool	is_operator(char c);
t_cmd *lexer(t_info *info);
bool	is_op(int op);
void print_cmd(t_cmd *cmd);
void print_all_cmd(t_cmd *cmd); 
const char *translate(int c);


// ls -la | grep .c | wc -l | cat -e 


#endif
