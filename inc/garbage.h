

#ifndef GARBAGE_H
#define GARBAGE_H

#include <stdlib.h>

typedef struct s_alloc {
  void *address;
  struct s_alloc *alloc_node;
  struct s_alloc *next;
} t_alloc;

void add_address(void *address, t_alloc *head);
void *chad_alloc(size_t size, int quantity, t_alloc *head);
void free_all(t_alloc *head);

#endif // !GARBAGE_H
