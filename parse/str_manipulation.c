

#include "macros.h"
#include "minish.h"

void count_quotes(char *line, t_info *info) {
  int i = 0;

  while (line[i]) {
    if (line[i] == DQUOTE || line[i] == QUOTE)
      info->quote_count++;
    i++;
  }
}
