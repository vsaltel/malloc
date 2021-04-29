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
	void	*ptr[10];

	ptr[0] = malloc(100);
	printf("%p\n", ptr[0]);
	show_alloc_mem();
	free(ptr[0]);
	return (0);
}
