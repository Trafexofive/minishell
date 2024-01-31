

#include "../inc/minish.h"

#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

void print_arr(char **str) {
  int i = -1;

  while (str[++i])
    printf("%s\n", str[i]);
}

bool is_space(char c) {
  if (c == ' ' || c == '\n' || c == '\t')
    return TRUE;
  return FALSE;
}
int after_quote(char *line, t_info *info) {
  int i = info->cursor;
  while (line[i]) {
    if (line[i] == DQUOTE || line[i] == QUOTE)
      return i;
    i++;
  }
  return -1;
}

t_oken **parse(const char *line);

void default_token(t_oken *head) {
  // default values for the token node;
  if (!head->next || !head->prev) {
    head->next = NULL;
    head->prev = NULL;
  }
  head->is_dollar = FALSE;
  head->quote_type = -1;
  head->data_type = -1;
}
// allocate for the token outside
t_oken *add_token(char *str_token, t_info *info) {
  size_t size = sizeof(t_oken);
  if (info->head == NULL) {
    t_oken *token = chad_alloc(size, 1, info->alloc_head);
    info->head = token;
    default_token(token);
    token->token = str_token;
    return (token);
  } else {
    t_oken *head_token = info->head;
    while (head_token->next != NULL) {
      head_token = head_token->next;
    }

    t_oken *token = chad_alloc(size, 1, info->alloc_head);
    default_token(token);
    head_token->next = token;
    token->prev = head_token;
    token->next = NULL;
    token->token = str_token;
    return (token);
  }
}

// syntax checking
void check_syntax(t_oken **tokens);

// tokenizing words and operators
t_oken *handle_quote(char *line, t_info *info) {
  // handling quotes by taking everything inside them regardless;
  char *str_token;
  t_oken *new_token;
  int j = -1;
  int i = info->cursor + 1;
  int end = after_quote(line, info);
  int len = end - info->cursor + 1;
  str_token = chad_alloc(sizeof(char), len, info->alloc_head);
  str_token[len] = '\0';
  while (str_token[++j]) {
    str_token[j] = line[i];
    i++;
  }
  new_token = add_token(str_token, info);
  if (line[info->cursor])
    info->cursor = end;
  return (new_token);
}

// return the index of end of quote + 1 aka first occurence of quote;

int keep_track_of_quote(char *line, t_info *info);

bool check_line(char *line, t_info *info) // for checking early parse errors
{
  printf("line ==> %s\n", line);
  while (line[info->cursor]) {
    if (!is_space(line[info->cursor]))
      break;
    info->cursor += 1;
  }
  printf("info cursor==>%d\n", info->cursor);
  return FALSE;
}
// such ar the '=' at the beggining
// will also return index of the first word occurence

// maybe for operators tokenize everything (word + op + word)
bool is_operator(char c) {
  if (c == PIPE || c == '>' || c == '<')
    return TRUE;
  return FALSE;
}

bool is_quote(char c) {
  if (c == DQUOTE || c == QUOTE)
    return TRUE;
  return FALSE;
}

int last_char_in_word(char *line, t_info *info) {
  int i = info->cursor;

  while (line[i] != '\0' && !is_space(line[i]) && !is_quote(line[i]))
    i++;
  i--;
  return (i);
}

void handle_operator(char *line, t_info *info) {
  if (line[info->cursor] == PIPE) {
    char *str_token = chad_alloc(1, 2, info->alloc_head);
    str_token[0] = '|';
    str_token[1] = '\0';
    add_token(str_token, info);
    info->cursor++;
  } else if (line[info->cursor] == '>') {
    if ((line[info->cursor + 1]) == '>') {
      char *str_token = ft_strdup(">>");
      add_token(str_token, info);
      info->cursor += 1;
    } else {
      char *str_token = ft_strdup(">");
      add_token(str_token, info);
    }
  } else if (line[info->cursor] == '<') {
    if (line[info->cursor++] == '<') {
      char *str_token = ft_strdup("<<");
      add_token(str_token, info);
      info->cursor += 1;
    } else {
      char *str_token = ft_strdup("<");
      add_token(str_token, info);
    }
  }
}

void handle_word(char *line, t_info *info) {
  char *str_token;
  int j = 0;
  int i = info->cursor;
  int end = last_char_in_word(line, info);
  int len = end - info->cursor + 1;
  str_token = chad_alloc(sizeof(char), len, info->alloc_head);
  while (j < len) {
    str_token[j] = line[i];
    j++;
    i++;
  }
  str_token[len] = '\0';
  info->cursor = end + 1;
  add_token(str_token, info);
}

void handle_dollar(char *line, t_info *info) {
  handle_word(line, info);
  return;
}

t_info *main_loop(char *line, t_info *info) {

  int len = ft_strlen(line);
  if (check_line(line, info) != FALSE)
    return NULL;
  while (info->cursor <= len) {
    if (line[info->cursor] == DQUOTE || line[info->cursor] == QUOTE)
      handle_quote(line, info);
    else if (is_operator(line[info->cursor]))
      handle_operator(line, info);
    else if (ft_isascii(line[info->cursor]))
      handle_word(line, info);
    else if (line[info->cursor] == '$')
      handle_dollar(line, info);

    info->cursor++;
  }
  return (info);
}

bool is_in(char c, const char *str);

void print_tokens(t_oken *head_token) {
  t_oken *ptr = head_token;
  while (ptr->next != NULL) {
    printf("token => %s   \n", ptr->token);
    ptr = ptr->next;
  }
}

int main(void) {
  t_info *info;
  char *line;
  t_alloc *alloc_head = ft_calloc(1, sizeof(t_alloc));

  line = readline("Lbroshell==>");
  info = ft_calloc(1, sizeof(t_info));
  info->line = line;
  info->alloc_head = alloc_head;
  info->head = NULL;
  puts("before main_loop>---------------");
  info->cursor = 0;

  add_address(line, alloc_head);
  main_loop(line, info);
  print_tokens(info->head);

  free(info);
  free_all(alloc_head);

  return EXIT_SUCCESS;
}
