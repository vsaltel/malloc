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
	ptr[1] = malloc(100);
	ptr[2] = malloc(100);
	free(ptr[1]);
	printf("|||\n");
	ptr[1] = malloc(104);
	printf("p %p %p %p\n", ptr[0], ptr[1], ptr[2]);
	printf("%lx %lx\n", sizeof(t_area), sizeof(t_mem));
	printf("3 %p %p %lu\n", (char *)ptr[0] + 100 + sizeof(t_mem) + 1, (char *)ptr[1] - sizeof(t_mem), (char *)ptr[1] - ((char *)ptr[0] + sizeof(t_mem) + 100));
	show_alloc_mem();
	free(ptr[0]);
	return (0);
}
