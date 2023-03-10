#include "my_malloc_free.h"
#include <stdio.h>
#include <stdlib.h>

// first thing to put in mind
// memory leak means allocating
// space in heap and losing its address

// get the head of linked list
// static varibale are stored in data segment in memory
// data segment is the last space that get freed in memory
// when main exit
// once the os find that the static varibale is pointing
// on a memory on the heap
// it automatically keep moving throw the linked list
// and free the allocated space
t_mal	*the_head(void)
{
	static t_mal	*head;

	if (!head)
	{
		head = malloc(sizeof(t_mal));
		head->ptr = 0;
		head->index = 0;
		head->next = NULL;
	}
	return (head);
}

// in case you freed a pointer before
// I use the same pointer to save the new allocate space
t_mal	*get_free_memory(int size)
{
	t_mal	*space;
	int		index;

	index = 0;
	space = the_head();
	while (space->next && space->next->ptr)
	{
		space = space->next;
		index = space->index + 1;
	}
	space->next = malloc(sizeof(t_mal));
	space->next->next = NULL;
	space->next->ptr = (uintptr_t)malloc(size);
	space->next->index = index;
	return (space->next);
}

uintptr_t	my_malloc(int size)
{
	t_mal	*available_memory;

	available_memory = get_free_memory(size);
	// printf("allocate in node %d\n", available_memory->index);
	return (available_memory->ptr);
}

void	my_free(void *address)
{
	uintptr_t	ptr;
	t_mal		*my_var;
	t_mal		*prev;

	ptr = (uintptr_t)address;
	my_var = the_head();
	while (my_var && my_var->ptr != ptr)
	{
		prev = my_var;
		my_var = my_var->next;
	}
	if (my_var && my_var->ptr == ptr)
	{
		prev->next = my_var->next;
		free(address);
		free(my_var);
	}
}

void	my_free_all(void)
{
	void	*ptr;
	t_mal	*my_var;
	t_mal	*prev;

	my_var = the_head()->next;
	while (my_var)
	{
		ptr = (void *)(my_var->ptr);
		prev = my_var;
		my_var = my_var->next;
		free(prev);
		free(ptr);
	}
	the_head()->next = NULL;
}
