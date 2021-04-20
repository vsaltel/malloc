#include "includes/malloc.h"
#include <stdio.h>

int	main(void)
{
	char	*ptr;
	int		size = 10;
	int		n;

	ptr = malloc(size);
	if (!ptr)
	{
		puts("alloc_fail");
		return (0);
	}
	n = 0;	
	while (n < size)
	{
		ptr[n] = (char)(n + 80);
		n++;
	}
	ptr[size - 1] = '\0';
	puts(ptr);	
	show_alloc_mem();
	free(ptr);
	return (0);
}
