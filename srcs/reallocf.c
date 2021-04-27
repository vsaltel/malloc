/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:35:03 by vsaltel           #+#    #+#             */
/*   Updated: 2021/04/27 14:35:06 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*get_mem_longer(t_area *area, t_mem *mem, size_t size)
{
	if ((!mem->next && mem->begin + size <= area->ptr + area->len) ||
		(mem->next && mem->begin + size <= mem->next->begin))
	{
		mem->end = mem->begin + size;
		mem->len = size;
		return (mem->begin);
	}
	return (NULL);
}

static void	*new_alloc(t_mem *mem, size_t size)
{
	t_mem	*ret;

	ret = malloc(size);
	if (ret)
	{
		ft_memcpy(ret, mem->begin, mem->len);
		free(mem->begin);
		return (ret);
	}
	return (NULL);
}

static void	*adjust_mem(t_area *area, t_mem *mem, size_t size)
{
	t_mem	*ret;

	if (!size)
		ret = new_alloc(mem, mem->len);
	else
	{
		ret = get_mem_longer(area, mem, size);
		if (!ret)
			ret = new_alloc(mem, size);
	}
	if (ret)
		return (ret);
	free(mem->begin);
	return (NULL);
}

void	*reallocf(void *ptr, size_t size)
{
	t_area	*area;
	t_mem	*mem;
	size_t	n;

	if (!ptr)
		return (malloc(size));
	area = g_malloc.area;
	n = 0;
	while (n < NB_AREA)
	{
		if (area[n].type != empty)
		{
			mem = get_mem_in_lst(ptr, area[n].lst);
			if (mem)
				return (adjust_mem(area + n, mem, size));
		}
		n++;
	}
	return (NULL);
}
