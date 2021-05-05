#include "../includes/malloc.h"
//#include <stdlib.h>
#include <stdio.h>

void	fill(char *ptr, int size)
{
	int		n;

	n = 0;	
	while (n < size)
	{
		ptr[n] = (char)(n + 48);
		n++;
	}
	ptr[size - 1] = '\0';
}

int	main(void)
{
	char	*ptr[10];

	ptr[0] = malloc(850);
	ptr[1] = malloc(850);
	ptr[2] = malloc(850);
	ptr[3] = malloc(850);
	ptr[4] = malloc(850);
	ptr[5] = malloc(850);
	fill(ptr[0], 850);
	fill(ptr[1], 850);
	fill(ptr[2], 850);
	fill(ptr[3], 850);
	fill(ptr[4], 850);
	fill(ptr[5], 850);
	show_alloc_mem();
	printf("%s %s\n", ptr[0], ptr[5]);
	free(ptr[2]);
	free(ptr[0]);
	free(ptr[1]);
	free(ptr[4]);
	free(ptr[5]);
	free(ptr[3]);
	return (0);
}

/*
int main(void)
{
	//g_area = NULL;
	int *ptr;

	ptr = calloc(sizeof(int), 4);
	ptr[0] = 0;
	ptr[1] = 100;
	ptr[2] = 900;
	ptr[3] = 19999900;
	//printf("\nhere\n");
	//printf("%d %d %d %d\n", ptr[0], ptr[1], ptr[2], ptr[3]);
	free(ptr);
	return (0);
}
*/
