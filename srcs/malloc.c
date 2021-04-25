#include "malloc.h"

t_malloc	g_malloc;

static void	*alloc_new_area(size_t size, t_type type)
{
	t_area	*area;
	t_mem	*mem;

	area = area_init(type, size);
	if (!area)
		return (NULL);
	mem = get_empty_mem(area->mem);
	if (!mem)
		return (NULL);
	if (!set_mem_in_area(area, mem, size))
		return (NULL);
	printf("new mem find %p %zu\n", mem->begin, mem->len);
	return (mem->begin);
}

static void	*alloc_in_area(size_t size, t_type type)
{
	t_area	*area;
	t_mem	*mem;

	area = get_area(g_malloc.area, type);
	if (!area)
		return (alloc_new_area(size, type));
	mem = get_empty_mem(area->mem);
	if (!mem || !set_mem_in_area(area, mem, size))
		return (alloc_new_area(size, type));
	printf("mem find %p %zu\n", mem->begin, mem->len);
	return (mem->begin);
}

void	*malloc(size_t size)
{
	if (!g_malloc.init)
		malloc_init();
	if (size > g_malloc.data_limit)
		return (NULL);
	if (size > g_malloc.page_size * 3)
		return (alloc_in_area(size, large));
	if (size > g_malloc.page_size / 3)
		return (alloc_in_area(size, small));
	return (alloc_in_area(size, tiny));
}
