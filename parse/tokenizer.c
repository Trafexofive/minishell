

#include "../inc/minish.h"



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
  t_oken  *iter = info->head;
  if (info->head == NULL) {
    t_oken *token = chad_alloc(size, 1, info->alloc_head);
    info->head = token;
    default_token(token);
    token->token = str_token;
    return (token);
  } else {
    while (iter->next != NULL) {
      iter = iter->next;
    }
    t_oken *token = chad_alloc(size, 1, info->alloc_head);
    default_token(token);
    iter->next = token;
    token->prev = iter;
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
  new_token = add_token(str_token, info);
  if (line[info->cursor - 1] == DQUOTE)
	new_token->quote_type = 1;
  else
	new_token->quote_type = 0;
  info->cursor += len;
  return (new_token);
}

// return the index of end of quote + 1 aka first occurence of quote;

int keep_track_of_quote(char *line, t_info *info);

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

void handle_operator(char *line, t_info *info) {
	t_oken *new_token;
  if (line[info->cursor] == PIPE) {
    char *str_token = chad_alloc(1, 2, info->alloc_head);
    str_token[0] = '|';
    str_token[1] = '\0';
    new_token = add_token(str_token, info);
	new_token->data_type = 5;
    info->cursor++;
  } else if (line[info->cursor] == '>') {
    if ((line[info->cursor + 1]) == '>') {
      char *str_token = ft_strdup(">>");
	  add_address(str_token, info->alloc_head);
      new_token = add_token(str_token, info);
	  new_token->data_type = 4;
      info->cursor += 2;
    } else {
      char *str_token = ft_strdup(">");
	  add_address(str_token, info->alloc_head);
      new_token = add_token(str_token, info);
	  new_token->data_type = 2;
      info->cursor += 1;
    }
  } else if (line[info->cursor] == '<') {
    if (line[info->cursor + 1] == '<') {
      char *str_token = ft_strdup("<<");
	  add_address(str_token, info->alloc_head);
      new_token = add_token(str_token, info);
	  new_token->data_type = 3;
      info->cursor += 2;
    } else {
      char *str_token = ft_strdup("<");
	  add_address(str_token, info->alloc_head);
      new_token = add_token(str_token, info);
	  new_token->data_type = 1;
      info->cursor += 1;
    }
  }
}

void handle_word(char *line, t_info *info) {
  char *str_token;
  t_oken *new_token;
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
  info->cursor = i;
  new_token =add_token(str_token, info);
	  new_token->data_type = 6;
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





int main(void) {
  t_info *info;
  char *line;
  t_alloc *alloc_head = ft_calloc(1, sizeof(t_alloc));

  alloc_head->next = NULL;
  info = ft_calloc(1, sizeof(t_info));
  alloc_head->address = info;
  line = ft_strdup("ls -la | grep a | tr a b | cat -e");
  info->line = line;
  info->alloc_head = alloc_head;
  info->head = NULL;
  info->cursor = 0;

//   add_address(line, alloc_head);
  main_loop(line, info);
  print_tokens(info->head);
	free(line);
  free_all(alloc_head);

  return EXIT_SUCCESS;
}
