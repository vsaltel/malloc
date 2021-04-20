#include "malloc.h"

static t_mem	*search_mem(void *ptr)
{
	size_t	n;

	n = 0;
	while (n < g_malloc.small_alloc && n < MAX_SMALL)
	{
		if (g_malloc.small[n].begin == ptr)
			return (&g_malloc.small[n]);
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
		return ;
	ret = munmap(mem->begin, mem->len);
	if (ret)
		puts("free fail");
}
