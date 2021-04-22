#include "malloc.h"

static t_mem	*search_mem(void *ptr)
{
	size_t	n;

	n = 0;
	while (n < MAX_TINY)
	{
		if (g_malloc.tiny[n].state && g_malloc.tiny[n].begin == ptr)
			return (&g_malloc.tiny[n]);
		n++;
	}
	n = 0;
	while (n < MAX_SMALL)
	{
		if (g_malloc.small[n].state && g_malloc.small[n].begin == ptr)
			return (&g_malloc.small[n]);
		n++;
	}
	n = 0;
	while (n < MAX_LARGE)
	{
		if (g_malloc.large[n].state && g_malloc.large[n].begin == ptr)
			return (&g_malloc.large[n]);
		n++;
	}
	return (NULL);
}

void	free(void *ptr)
{
	t_mem	*mem;
	int		ret;

	mem = search_mem(ptr);
	if (!mem)
	{
		printf("free fail %p\n", ptr);
		return ;
	}
	ret = munmap(mem->begin, mem->len);
	mem->state = 0;
	if (ret)
		printf("free fail %p\n", ptr);
	printf("free work %p\n", ptr);
}
