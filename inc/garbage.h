

#ifndef GARBAGE_H
#define GARBAGE_H

#include <stdlib.h>

typedef struct s_alloc {
  void *address;
  struct s_alloc *next;
} t_alloc;

void *chad_alloc(size_t size, int quantity, t_alloc *first_adress);
void free_all(t_alloc *head);

#endif // !GARBAGE_H
