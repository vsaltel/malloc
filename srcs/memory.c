#include "malloc.h"

t_mem	*get_mem_in_lst(void *ptr, t_mem *mem)
{
	while (mem)
	{
		if (ptr >= mem->begin && ptr <= mem->end)
			return (mem);
		mem = mem->next;
	}
	return (NULL);
}

t_mem	*get_empty_mem(t_mem *mem)
{
	size_t	n;	

	n = 0;
	while (n < AREA_MAX_ALLOC)
	{
		if (!mem[n].state)
			return (&mem[n]);
		n++;
	}
	return (NULL);
}

static t_mem	*set_mem(t_area *area, t_mem *mem, size_t size, t_mem *bef)
{
	if (!bef)
	{
		mem->begin = area->ptr;
		mem->len = size;
		mem->end = area->ptr + size;
		mem->state = 1;
		area->lst = mem;
	}
	else
	{
		mem->begin = bef->end + 1;
		mem->len = size;
		mem->end = mem->begin + size;
		mem->state = 1;
		if (bef->next)
			mem->next = bef->next;
		bef->next = mem;
	}
	return (mem);
}

t_mem	*set_mem_in_area(t_area *area, t_mem *mem, size_t size)
{
	t_mem	*tmp;

	tmp = area->lst;
	if (!tmp && (size_t)(area->ptr + area->len) >= size)
		return (set_mem(area, mem, size, NULL));
	else if (tmp && tmp->begin != area->ptr && (size_t)(tmp->begin - area->ptr) >= size)
	{
		mem->next = tmp;
		return (set_mem(area, mem, size, NULL));
	}
	while (tmp)
	{
		if (!tmp->next && (size_t)((area->ptr + area->len) - (tmp->end + 1)) >= size)
			return (set_mem(area, mem, size, tmp));
		else if (tmp->next && (size_t)(tmp->next->begin - (tmp->end + 1)) >= size)
			return (set_mem(area, mem, size, tmp));
		tmp = tmp->next;
	}
	return (NULL);
}
