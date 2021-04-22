#include "malloc.h"

t_malloc	g_malloc;

static void	malloc_init(void)
{
	struct rlimit	rlp;
	size_t			n;

	n = 0;
	while (n < MAX_TINY)
		g_malloc.tiny[n++].state = 0;
	n = 0;
	while (n < MAX_SMALL)
		g_malloc.small[n++].state = 0;
	n = 0;
	while (n < MAX_LARGE)
		g_malloc.large[n++].state = 0;

	getrlimit(RLIMIT_DATA, &rlp);
	g_malloc.data_limit = rlp.rlim_cur;
	g_malloc.page_size = (size_t)getpagesize();
	g_malloc.init = 1;
}

static void	*alloc_large(size_t size)
{
	void	*ptr;
	size_t	n;

	n = 0;
	while (n < MAX_LARGE && g_malloc.large[n].state)
		n++;
	if (n >= MAX_LARGE)
		return (NULL);
	printf("there %p\n", (void *)ADDR_LARGE);
	ptr = mmap((void *)ADDR_LARGE, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, 0, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	g_malloc.large[n].begin = ptr;
	g_malloc.large[n].end = ptr + size;
	g_malloc.large[n].len = size;
	g_malloc.large[n].state = 1;
	return (ptr);
}

static void	*alloc_small(size_t size)
{
	void	*ptr;
	size_t	n;

	n = 0;
	while (n < MAX_SMALL && g_malloc.small[n].state)
		n++;
	if (n >= MAX_SMALL)
		return (NULL);
	ptr = mmap((void *)ADDR_SMALL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, 0, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	g_malloc.small[n].begin = ptr;
	g_malloc.small[n].end = ptr + size;
	g_malloc.small[n].len = size;
	g_malloc.small[n].state = 1;
	return (ptr);
}

static void	*alloc_tiny(size_t size)
{
	void	*ptr;
	size_t	n;

	n = 0;
	while (n < MAX_TINY && g_malloc.tiny[n].state)
		n++;
	if (n >= MAX_TINY)
		return (NULL);
	ptr = mmap((void *)ADDR_TINY, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, 0, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	g_malloc.tiny[n].begin = ptr;
	g_malloc.tiny[n].end = ptr + size;
	g_malloc.tiny[n].len = size;
	g_malloc.tiny[n].state = 1;
	return (ptr);
}

void	*malloc(size_t size)
{
	if (!g_malloc.init)
		malloc_init();
	if (size > g_malloc.data_limit)
		return (NULL);
	if (size > 1000)
		return (alloc_large(size));
	if (size > 100)
		return (alloc_small(size));
	return (alloc_tiny(size));
}
