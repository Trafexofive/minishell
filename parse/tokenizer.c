

#include "../inc/minish.h"

#include <stdio.h>
#include <unistd.h>

void parse_error(const char *exit_msg, t_info *info) {
  printf("%s\n", exit_msg);
  free_all(info->alloc_head);
  exit(1);
}

void print_arr(char **str) {
  int i = -1;

  while (str[++i])
    printf("%s\n", str[i]);
}

bool is_space(char c) {
  if (c == ' ' || c == '\t')
    return TRUE;
  return FALSE;
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

int quote_len(char *line, t_info *info) {
  int i = info->cursor;
  int j = 0;
  while (line[i]) {
    if (line[i] == 34 || line[i] == 39)
      return j;
    i++;
    j++;
  }
  return -1;
}

// tokenizing words and operators
t_oken *handle_quote(char *line, t_info *info) {
  // handling quotes by taking everything inside them regardless;
  // update quote type
  char *str_token;
  t_oken *new_token;
  int j = 0;
  info->cursor += 1;
  int i = info->cursor;
  int len = quote_len(line, info) + 1;
  str_token = chad_alloc(sizeof(char), len, info->alloc_head);
  while (i < len) {
    str_token[j] = line[i];
    j++;
    i++;
  }
  str_token[len] = '\0';
  printf(" str_token ==> |%s|\n", str_token);
  new_token = add_token(str_token, info);
  info->cursor += len;
  printf(" after quote cursor %d\n", info->cursor);
  return (new_token);
}

// return the index of end of quote + 1 aka first occurence of quote;

int keep_track_of_quote(char *line, t_info *info);

bool valid_quotes(t_info *info) {
  char *line = info->line;
  int i = 0;
  int quote_c = 0;
  int dquote_c = 0;
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
  return TRUE;
}

bool check_line(char *line, t_info *info) // for checking early parse errors
{
  if (!valid_quotes(info))
    return FALSE;
  while (line[info->cursor]) {
    if (!is_space(line[info->cursor]))
      break;
    info->cursor += 1;
  }
  return TRUE;
} // such ar the '=' at the beggining
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

int word_len(t_info *info) {
  int i = info->cursor;
  int j = 0;

  while (info->line[i] != '\0' && !is_space(info->line[i]) &&
         !is_quote(info->line[i])) {
    i++;
    j++;
  }
  return (j);
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
      info->cursor += 2;
    } else {
      char *str_token = ft_strdup(">");
      add_token(str_token, info);
      info->cursor += 1;
    }
  } else if (line[info->cursor] == '<') {
    if (line[info->cursor + 1] == '<') {
      char *str_token = ft_strdup("<<");
      add_token(str_token, info);
      info->cursor += 2;
    } else {
      char *str_token = ft_strdup("<");
      add_token(str_token, info);
      info->cursor += 1;
    }
  }
}

void handle_word(char *line, t_info *info) {
  char *str_token;
  int j = 0;
  int i = info->cursor;
  int len = word_len(info);
  printf("word len ==> %d\n", len);
  str_token = chad_alloc(sizeof(char), len, info->alloc_head);
  while (j < len) {
    str_token[j] = line[i];
    j++;
    i++;
  }
  str_token[len] = '\0';
  // printf(" word str token ==> %s\n", str_token);
  info->cursor = i;
  add_token(str_token, info);
}

void handle_dollar(char *line, t_info *info) {
  handle_word(line, info);
  return;
}

t_info *main_loop(char *line, t_info *info) {

  if (!check_line(line, info))
    return NULL;
  while (line[info->cursor]) {
    if (line[info->cursor] == DQUOTE || line[info->cursor] == QUOTE)
      handle_quote(line, info);
    else if (is_operator(line[info->cursor]))
      handle_operator(line, info);
    else if (ft_isprint(line[info->cursor]) && !is_space(line[info->cursor])) {
      handle_word(line, info);
    } else if (line[info->cursor] == '$')
      handle_dollar(line, info);
    if (!line[info->cursor])
      break;

    info->cursor++;
  }
  fprintf(stderr, "%s", "break\n");
  return (info);
}

bool is_in(char c, const char *str);

void print_tokens(t_oken *head_token) {
  t_oken *ptr = head_token;
  if (ptr->next == NULL)
    printf("token => %s   \n", ptr->token);
  else {
    while (ptr->next != NULL) {
      printf("token => %s   \n", ptr->token);
      ptr = ptr->next;
    }
  }
}

int main(void) {
  t_info *info;
  char *line;
  t_alloc *alloc_head = ft_calloc(1, sizeof(t_alloc));

  line = ft_strdup("   ls -la > |    test   >>");
  info = ft_calloc(1, sizeof(t_info));
  info->line = line;
  info->alloc_head = alloc_head;
  info->head = NULL;
  info->cursor = 0;

  add_address(line, alloc_head);
  main_loop(line, info);
  print_tokens(info->head);

  free(info);
  free_all(alloc_head);

  return EXIT_SUCCESS;
}
