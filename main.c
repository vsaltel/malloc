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
	//char	*ptr[10];
	uint8_t	*t;

	t = calloc(sizeof(uint8_t), 2);
	t[0] = 256;
	t[1] = 256;
	//fill(ptr[0], 103);
	show_alloc_mem_ex();
	printf("%d %d\n", t[0], t[1]);
	free(t);
	return (0);
}
