

#include "../inc/minish.h"

t_oken **parse(const char *line);

bool check_line(char *line, t_info *info) // for checking early parse errors
{
  if (!valid_quotes(info))
    return FALSE;
  while (line[info->cursor]) {
    if (!is_space(line[info->cursor])) 
      return TRUE;
    info->cursor += 1;
  }
  return FALSE;
} // such ar the '=' at the beggining

void default_token(t_oken *head) {
  // default values for the token node;
  if (!head->next || !head->prev) {
    head->next = NULL;
    head->prev = NULL;
  }
  head->dollar_presence = FALSE;
  head->quote_type = -1;
  head->data_type = -1;
}
// allocate for the token outside
t_oken *add_token(char *str_token, t_info *info) {
  size_t size = sizeof(t_oken);
  // t_oken *iter = info->head;
  t_oken *head = info->head;
  if (!info->head) {
    t_oken *token = chad_alloc(size, 1, info->alloc_head);
    info->head = token;
    default_token(token);
    token->token = str_token;
    return (token);
  } else {
    while (head->next != NULL) {
      head = head->next;
    }
    t_oken *token = chad_alloc(size, 1, info->alloc_head);
    default_token(token);
    head->next = token;
    token->prev = head;
    token->next = NULL;
    token->token = str_token;
    return (token);
  }
}
void handle_operator(char *line, t_info *info) {
  t_oken *new_token;
  if (line[info->cursor] == '|') {
    char *str_token = chad_alloc(1, 2, info->alloc_head);
    str_token[0] = '|';
    str_token[1] = '\0';
    new_token = add_token(str_token, info);
    new_token->data_type = 5;
    info->cursor += 1;
  } 
  else if (line[info->cursor] == '>') {
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
// syntax checking
void check_syntax(t_oken **tokens);

// tokenizing words and operators

void  join_quotes(t_oken *head)
{
  t_oken *token = head;
  t_oken *next = head->next;
  while (next)
  {
    if (/*token->quote_type == next->quote_type && */token->join_next == TRUE)
    {
      token->token = ft_strjoin(token->token, next->token);
      token->next = next->next;
      next = next->next;
    }
    else
    {
      token = next;
      next = next->next;
    }
  }
}

t_oken *handle_quote(char *line, t_info *info) {
  // handling quotes by taking everything inside them regardless;
  // update quote type
  //quotes not working if they are the last token
  char *str_token;
  t_oken *new_token;
  int j = 0;
  info->cursor += 1;
  int i = info->cursor;
  int len = quote_len(line, info);
  if (len == -1)
    return NULL;
  str_token = (char *)chad_alloc(1, len, info->alloc_head);
  while (j < len) {
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
  new_token->data_type = WORD;
  // does not support different quotes joining
  // flag the in handle_word and join them
  if (line[i + 1] == DQUOTE && new_token->quote_type == 1)
    new_token->join_next = TRUE;
  else if (line[i + 1] == QUOTE && new_token->quote_type == 0)
    new_token->join_next = TRUE;
  else
    new_token->join_next = FALSE;
  info->cursor += j + 1;
  return (new_token);
}

t_oken *handle_word(char *line, t_info *info) {
  char *str_token;
  t_oken *new_token;
  int j = 0;
  int i = info->cursor;
  int len = word_len(info);
  str_token = chad_alloc(sizeof(char), len + 1, info->alloc_head); // segv here
  while (j < len) {
    str_token[j] = line[i];
    j++;
    i++;
  }
  str_token[len] = '\0';
  info->cursor = i;
  new_token = add_token(str_token, info);
  new_token->data_type = 6;
  return (new_token);
}

void handle_dollar(char *line, t_info *info) {
  t_oken *new_token = handle_word(line, info);
  new_token->dollar_presence = TRUE;
}

t_info *main_loop(char *line, t_info *info) {

  if (!check_line(line, info))
    return NULL;
  while (line[info->cursor]) {
    if (is_operator(line[info->cursor]))
    {
      handle_operator(line, info);
    }
    else if (line[info->cursor] == DQUOTE || line[info->cursor] == QUOTE)
    {
      handle_quote(line, info);
    }
    else if (ft_isprint(line[info->cursor]) && !is_space(line[info->cursor]) && !is_operator(line[info->cursor]) && !is_quote(line[info->cursor]))
    {

      handle_word(line, info);
    }
    else if (line[info->cursor] == '$')
      handle_dollar(line, info);
    else if (is_space(line[info->cursor]))
      info->cursor++;
  }

  return (info);
}

void print_all_cmd(t_cmd *cmd) 
{
  while (cmd) {
    print_cmd(cmd);
    cmd = cmd->next;
    if (cmd == NULL)
      break;
  }
}

void  readline_loop(t_info *info)
{
  char *line;
  t_cmd *cmd;
    t_alloc *alloc_head = ft_calloc(1, sizeof(t_alloc));
  alloc_head->next = NULL;
  info = ft_calloc(1, sizeof(t_info));
  alloc_head->address = info;
  info->alloc_head = alloc_head;
  info->head = NULL;
  while (1)
  {
    info->cursor = 0;
    line = readline("minishell$ ");
    if (!line)
    {
      break;
    }
    if (line[0] == '\0')
    {
      free(line);
      continue;
    }
    info->line = line;
    main_loop(line, info);
    join_quotes(info->head);
    cmd = lexer(info);
    print_all_cmd(cmd);
    free_all(alloc_head);
    info->alloc_head->address = NULL;
    info->head = NULL;
    free(line);



    free(info);
  }
}

int main(void) {
  t_info *info;
  // char *line;
  // t_cmd *cmd;

  
  readline_loop(info);
  return EXIT_SUCCESS;
}


// int main(void) {
//   t_info *info;
//   char *line;
//   t_alloc *alloc_head = ft_calloc(1, sizeof(t_alloc));
//   // t_cmd *cmd;

//   alloc_head->next = NULL;
//   info = ft_calloc(1, sizeof(t_info));
//   alloc_head->address = info;
//   info->alloc_head = alloc_head;
//   info->head = NULL;
  
//   line = readline("minishell$ ");
//   // if (!line)
//   //   break;
//   if (line[0] == '\0')
//     return (0);

//   info->line = line;
//   info->cursor = 0;
//   main_loop(line, info);
//   join_quotes(info->head);
//   // print_tokens(info->head);
//   cmd = lexer(info);
//   // print_all_cmd(cmd);
//     free(line);
//   // free(line);
//   free_all(alloc_head);

//   //   add_address(line, alloc_head);
//   // free(line);

//   return EXIT_SUCCESS;
// }
