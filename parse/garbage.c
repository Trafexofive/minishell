
#include "../inc/garbage.h"
#include "../libft/libft.h"
#include <stdio.h>

static t_alloc *first_adress;

void alloc_append_last(void *alloc_ptr) {
  if (!first_adress)
    first_adress = ft_calloc(1, sizeof(t_alloc));
  if (!first_adress->address)
    first_adress->address = alloc_ptr;
  else {
    while (first_adress->next != NULL) {
      first_adress = first_adress->next;
    }
    t_alloc *new_alloc_node = first_adress;
    first_adress->next = new_alloc_node;
    new_alloc_node->address = alloc_ptr;
    new_alloc_node->next = NULL;
  }
}

void free_all(void) {
  while (first_adress->next != NULL) {
    free(first_adress->address);
    first_adress = first_adress->next;
  }
}

void *chad_alloc(size_t size, int quantity) {
  void *alloc_ptr;

  alloc_ptr = malloc(size * quantity);
  if (!alloc_ptr)
    return (NULL);
  if (!first_adress)
    first_adress = ft_calloc(1, sizeof(t_alloc));
  if (!first_adress->address) {
    first_adress->address = alloc_ptr;
  } else {
    alloc_append_last(alloc_ptr);
  }
  return (alloc_ptr);
}
