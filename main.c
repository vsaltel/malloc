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
	ptr[1] = malloc(101);
	ptr[2] = malloc(101);
	free(ptr[1]);
	ptr[1] = malloc(101);
	ptr[3] = malloc(10000);
	show_alloc_mem();
	free(ptr[0]);
	free(ptr[1]);
	free(ptr[2]);
	free(ptr[3]);
	free((void *)0x5);
	return (0);
}
