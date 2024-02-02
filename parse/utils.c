

#include "../inc/minish.h"

void parse_error(const char *exit_msg, t_info *info) {
  printf("%s\n", exit_msg);
  free_all(info->alloc_head);
  exit(1);
}

void print_arr(char **str) {
  int i;

  i = -1;
  while (str[++i])
    printf("%s\n", str[i]);
}

bool is_space(char c) {
  if (c == ' ' || c == '\t')
    return (TRUE);
  return (FALSE);
}
int quote_len(char *line, t_info *info) {
  int i;
  int j;

  i = info->cursor;
  j = 0;
  if (line[i - 1] == 34)
  {
    while (line[i])
    {
      if (line[i] == 34)
        return (j);
      i++;
      j++;
    }
  }
  else if (line[i - 1] == 39)
  {
  while (line[i]) {
    if (line[i] == 39)
      return (j);
    i++;
    j++;
  }

  }
  return (-1);
}

bool is_operator(char c) {
  if (c == PIPE || c == '>' || c == '<')
    return (TRUE);
  return (FALSE);
}

bool is_quote(char c) {
  if (c == DQUOTE || c == QUOTE)
    return (TRUE);
  return (FALSE);
}

int last_char_in_word(char *line, t_info *info) {
  int i;

  i = info->cursor;
  while (line[i] != '\0' && !is_space(line[i]) && !is_quote(line[i]))
    i++;
  i--;
  return (i);
}

int word_len(t_info *info) {
  int i;
  int j;

  i = info->cursor;
  j = 0;
  while (info->line[i] != '\0' && !is_space(info->line[i]) &&
         !is_quote(info->line[i]) && !is_operator(info->line[i])){
    i++;
    j++;
  }
  return (j);
}
bool valid_quotes(t_info *info) {
  char *line;
  int i;
  int quote_c;
  int dquote_c;

  line = info->line;
  i = 0;
  quote_c = 0;
  dquote_c = 0;
  while (line[i]) {
    if (line[i] == DQUOTE)
      dquote_c++;
    if (line[i] == DQUOTE)
      quote_c++;
    i++;
  }
  if (dquote_c % 2 != 0 && dquote_c != 0) {
    puts("invalid quotes");
    parse_error("invalid quotes", info);
  }
  if (quote_c % 2 != 0 && quote_c != 0) {
    puts("invalid quotes");
    parse_error("invalid quotes", info);
  }
  return (TRUE);
}

const char *translate(int c) {
  if (c == 1)
    return ("REDIR_IN");
  if (c == 2)
    return ("REDIR_OUT");
  if (c == 3)
    return ("heredoc");
  if (c == 4)
    return ("herestring");
  if (c == 5)
    return ("PIPE");
  if (c == 6)
    return ("WORD");
  return NULL;
}

void print_tokens(t_oken *head_token) {
  t_oken *ptr = head_token;
  while (ptr->next != NULL) {
    printf("token :%s--quote value =>%d--type =>%s \n", ptr->token,
           ptr->quote_type, translate(ptr->data_type));
    ptr = ptr->next;
  }
    printf("token :%s--quote value =>%d--type =>%s \n", ptr->token,
           ptr->quote_type, translate(ptr->data_type));
}
