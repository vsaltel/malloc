#include "malloc.h"

static int	free_mem(t_area *area, t_mem *mem)
{
	int		ret;
	t_mem	*tmp;

	lala = 2
	ret = 0;
	if (area->lst == mem)
		area->lst = mem->next;
	else
	{
		tmp = area->lst;
		while (tmp)
		{
			if (tmp->next && tmp->next == mem)
			{
				tmp->next = mem->next;
				break ;
			}
			tmp = tmp->next;
		}
	}
	mem->state = 0;
	if (area->lst == NULL)
	{
		printf("munmap area %p\n", area->ptr);
		ret = munmap(area->ptr, area->len);
		area->type = empty;
	}
	return (ret);
}

static int	search_mem(void *ptr)
{
	t_area	*area;
	t_mem	*mem;
	size_t	n;

	area = g_malloc.area;
	n = 0;
	while (n < NB_AREA)
	{
		if (area[n].type != empty)
		{
			mem = get_mem_in_lst(ptr, area[n].lst);
			if (mem)
				return (free_mem(area + n, mem));
		}
		n++;
	}
	return (1);
}

void	free(void *ptr)
{
	int		ret;

	if (!ptr)
		return ;
	ret = search_mem(ptr);
	if (ret == 1)
	{
		printf("free fail : not find %p\n", ptr);
		return ;
	}
	else if (ret)
		printf("free fail : munmap fail %p\n", ptr);
}
