#include "../includes/malloc.h"

int	main(void)
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 1)
	{
		addr = (char *)malloc(1024);
		addr[0] = 42;
		i++;
	}
	show_alloc_mem();
	return (0);
}
