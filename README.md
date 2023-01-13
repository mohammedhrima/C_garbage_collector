
to check the program:
	run make
	
my_malloc(site_t size_to_allocate);
my_free(void *ptr, int free_all)

my_malloc: is like malloc you give it the size you want to allocate 
	
my_free:   is like default free but has a second argument,
     		   in case you want to free all allocated space once set free_all to 1 else set it to 

example:
				char ***ptr = my_malloc(1000);
				my_free(ptr, 0)

to use it,
include the header -> #include "my_malloc_free/my_malloc_free.h"
and compile it like this: gcc my_malloce_free/my_malloc_free.c your_file.c
