
#include "../inc/garbage.h"
#include "../libft/libft.h"
#include <stdio.h>

void *chad_alloc(size_t size, int quantity, t_alloc *first_adress) {
  void *alloc_ptr;

  alloc_ptr = malloc(size * quantity);
  if (!alloc_ptr)
    return (NULL);
  if (first_adress == NULL) {

    first_adress = ft_calloc(1, sizeof(t_alloc));
    first_adress->address = alloc_ptr;
  } else {
    while (first_adress->next != NULL) {
      first_adress = first_adress->next;
    }
    t_alloc *new_alloc_node = first_adress;
    first_adress->next = new_alloc_node;
    new_alloc_node->address = alloc_ptr;
    new_alloc_node->next = NULL;
  }
  return (alloc_ptr);
}

void free_all(t_alloc *head) {
  while (head->next != NULL) {
    free(head->address);
    head = head->next;
  }
}
