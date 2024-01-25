

#include "libft/libft.h"
#include "minish.h"

static t_alloc *first_adress;
static t_oken *head_token;

t_oken **parse(const char *line);
void alloc_append_last(void *alloc_ptr) {
  t_alloc new_alloc_node;
  while (first_adress->next != NULL) {
    first_adress = first_adress->next;
  }
  first_adress->next = &new_alloc_node;
  new_alloc_node.address = alloc_ptr;
}

void free_all(void) {
  while (first_adress->next != NULL) {
    free(first_adress->address);
    first_adress->next;
  }
}

void *chad_alloc(size_t size, int quantity) {
  void *alloc_ptr;

  alloc_ptr = malloc(size * quantity);
  if (alloc_ptr == NULL)
    return (NULL);
  if (first_adress == NULL)
    first_adress = alloc_ptr;
  else {
    alloc_append_last(alloc_ptr);
  }
  return (alloc_ptr);
}

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
t_oken *add_token(char *str_token) {
  size_t size = sizeof(t_oken);
  while (head_token->next != NULL) {
    head_token = head_token->next;
    if (head_token == NULL) {
      t_oken *token = chad_alloc(size, 1);
      head_token->token = str_token;
      default_token(head_token);
    } else {
      t_oken *token = chad_alloc(size, 1);
      head_token->token = str_token;
    }
  }
}

void print_arr(char **str) {
  int i = -1;

  while (str[++i])
    printf("%s\n", str[i]);
}
// add and lex
void *add_token_smart(size_t size, int index, int end, char **str);
// maybe call it auto add;

bool is_space(char c) {
  if (c == ' ' || c == '\n' || c == '\t')
    return TRUE;
  return FALSE;
}
// syntax checking
void check_syntax(t_oken **tokens);

t_oken **tokenize(char *line) {
  char **tokens;

  tokens = ft_split(line, ' ');
  print_arr(tokens);
  return (NULL);
}

void tokenize_word(char *token, t_info info);
void tokenize_operator(char *token);
// tokenizing words and operators
void handle_quote(char *line, t_info line_info) {
  // handling quotes by taking everything inside them regardless;
}

bool check_line(char *line, t_info *info); // for checking early parse errors
                                           // such ar the '=' at the beggining
// will also return index of the first word occurence

// maybe for operators tokenize everything (word + op + word)
bool is_operator(char *line);

void main_loop(char *line, t_info *info) {
  int i;

  i = check_line(line);

  while (line[i]) {
    if (line[i] == DQUOTE || line[i] == QUOTE)
      handle_quote(line);
    else if (is_operator(line[i]))

      i++;
  }
}

t_oken **parse(const char *line) { return (NULL); }

int main(void) {
  t_info *info;
  char *line;

  line = ft_strdup("ls -la > hello.txt");
  info = chad_alloc(sizeof(t_info), 1);
  main_loop(line, info);

  return EXIT_SUCCESS;
}
