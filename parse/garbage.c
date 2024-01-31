
#include "../inc/garbage.h"
#include "../libft/libft.h"
#include <stdio.h>

void add_address(void *address, t_alloc *head) {
  while (head->next != NULL)
    head = head->next;
  t_alloc *new_alloc_node = ft_calloc(1, sizeof(t_alloc));
  head->next = new_alloc_node;
  new_alloc_node->address = address;
  new_alloc_node->alloc_node = new_alloc_node;
  new_alloc_node->next = NULL;
}

void *chad_alloc(size_t size, int quantity, t_alloc *first_adress) {
  void *alloc_ptr;

  alloc_ptr = malloc(size * quantity);
  if (!alloc_ptr)
    return (NULL);
  if (first_adress == NULL) {

    first_adress = ft_calloc(1, sizeof(t_alloc));
    first_adress->alloc_node = first_adress;
    first_adress->address = alloc_ptr;
    first_adress->next = NULL;
  } else {
    while (first_adress->next != NULL) {
      first_adress = first_adress->next;
    }
    t_alloc *new_alloc_node = ft_calloc(1, sizeof(t_alloc));
    new_alloc_node->alloc_node = new_alloc_node;
    new_alloc_node = first_adress;
    first_adress->next = new_alloc_node;
    new_alloc_node->address = alloc_ptr;
    new_alloc_node->next = NULL;
  }
  return (alloc_ptr);
}

void free_all(t_alloc *head) {
  while (head->next != NULL) {
    free(head->address);
    free(head->alloc_node);
    head = head->next;
  }
}
