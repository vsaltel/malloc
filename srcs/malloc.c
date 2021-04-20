#include "malloc.h"

t_malloc	g_malloc;

static void	malloc_init(void)
{
	struct rlimit	rlp;

	g_malloc.tiny_alloc = 0;
	g_malloc.small_alloc = 0;
	g_malloc.large_alloc = 0;

	getrlimit(RLIMIT_DATA, &rlp);
	g_malloc.data_limit = rlp.rlim_cur;
	g_malloc.page_size = (size_t)getpagesize();
	g_malloc.init = 1;
}

static void	*alloc_tiny(size_t size)
{
	void	*ptr;
	size_t	n;

	if (g_malloc.tiny_alloc > MAX_TINY)
		return (NULL);
	ptr = mmap((void *)ADDR_TINY, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, 0, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	n = ++g_malloc.tiny_alloc;
	g_malloc.tiny[n].begin = ptr;
	g_malloc.tiny[n].end = ptr + size;
	g_malloc.tiny[n].len = size;
	return (ptr);
}

void	*malloc(size_t size)
{
	if (!g_malloc.init)
		malloc_init();
	if (size > g_malloc.data_limit)
		return (NULL);
	return (alloc_tiny(size));
}
