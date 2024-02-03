
#include "../inc/garbage.h"
#include "../libft/libft.h"
#include <stdio.h>

void add_address(void *address, t_alloc *head) {
	t_alloc *iter = head;
  // puts("adding address");
  while (iter->next != NULL) {
	iter = iter->next;
  }
  t_alloc *new_alloc_node = ft_calloc(1, sizeof(t_alloc));
  head = iter;
  head->next = new_alloc_node;
  // printf("address: %p\n", new_alloc_node);
  new_alloc_node->address = address;
  new_alloc_node->alloc_node = new_alloc_node;
  new_alloc_node->next = NULL;
}

void *chad_alloc(size_t size, int quantity, t_alloc *first_adress) {
  void *alloc_ptr;
  t_alloc *iter = first_adress;

  alloc_ptr = ft_calloc(size ,quantity);
  if (!alloc_ptr)
    return (NULL);
  // fprintf(stderr, "break\n");
  // fprintf(stderr, "address: %p\n", first_adress);
    while (iter->next != NULL) {
      iter = iter->next;
    }
	// puts("adding address");
    t_alloc *new_alloc_node = ft_calloc(1, sizeof(t_alloc));
    new_alloc_node->alloc_node = new_alloc_node;
    // printf("node address: %p\n", new_alloc_node->alloc_node);
    
    iter->next = new_alloc_node;
    new_alloc_node->address = alloc_ptr;
    // printf("address: %p\n", new_alloc_node->address);
    new_alloc_node->next = NULL;
  return (alloc_ptr);
}

void free_all(t_alloc *head) {
  t_alloc *tmp;
  // head = head->next;
  //skipping info struct
  while (head->next != NULL) {
    // puts("freeing");
    tmp = head;
    head = head->next;
    if (tmp->address)
    {
      puts("freeing");
    free(tmp->address);
    free(tmp->alloc_node);
    tmp->address = NULL;
    tmp->alloc_node = NULL;
    }
	// puts("freeing");
  }
    // free(head->address);
    // free(head->alloc_node);
}
