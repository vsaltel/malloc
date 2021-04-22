#include "includes/malloc.h"
#include <stdio.h>

int	main(void)
{
	char	*ptr;
	int		size = 101;
	int		n;

	printf("alloc\n");
	ptr = malloc(size);
	if (!ptr)
	{
		puts("alloc_fail");
		return (0);
	}
	printf("fill\n");
	n = 0;	
	while (n < size)
	{
		ptr[n] = (char)(n + 40);
		n++;
	}
	ptr[size - 1] = '\0';
	printf("print\n");
	puts(ptr);	
	printf("show\n");
	show_alloc_mem();
	free(ptr);
	free((void *)0x5);
	return (0);
}
