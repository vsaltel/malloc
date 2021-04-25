#include "includes/malloc.h"
#include <stdio.h>

void	fill(char *ptr, int size)
{
	int		n;

	n = 0;	
	while (n < size)
	{
		ptr[n] = (char)(n + 40);
		n++;
	}
	ptr[size - 1] = '\0';
}

int	main(void)
{
	char	*ptr[10];

	ptr[0] = malloc(101);
	ptr[1] = malloc(300);
	ptr[2] = malloc(101);
	free(ptr[1]);
	ptr[0] = realloc(ptr[0], 200);
	show_alloc_mem();
	free(ptr[0]);
	return (0);
}
