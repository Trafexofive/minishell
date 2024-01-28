

#ifndef GARBAGE_H
#define GARBAGE_H

#include <stdlib.h>

typedef struct s_alloc {
  void *address;
  struct s_alloc *next;
} t_alloc;

void alloc_append_last(void *alloc_ptr);
void *chad_alloc(size_t size, int quantity);
void free_all(void);

#endif // !GARBAGE_H
