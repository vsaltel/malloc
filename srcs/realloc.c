/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:34:56 by vsaltel           #+#    #+#             */
/*   Updated: 2021/04/29 16:53:43 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*get_mem_longer(t_area *area, t_mem *mem, size_t size)
{
	if ((!mem->next && mem + sizeof(t_mem) + size <= area->ptr + (area->len - sizeof(t_area))) ||
		(mem->next && mem + sizeof(t_mem) + size <= mem->next + sizeof(t_mem)))
	{
		mem->len = size + sizeof(t_mem);
		return (mem + sizeof(t_mem));
	}
	return (NULL);
}

static void	*new_alloc(t_mem *mem, size_t size)
{
	t_mem	*ret;

	ret = malloc(size);
	if (ret)
	{
		ft_memcpy(ret, mem + sizeof(t_mem), mem->len - sizeof(t_mem));
		free(mem);
		return (ret);
	}
	return (NULL);
}

static void	*adjust_mem(t_area *area, t_mem *mem, size_t size)
{
	t_mem	*ret;

	if (!size)
		ret = new_alloc(mem, mem->len - sizeof(t_mem));
	else
	{
		ret = get_mem_longer(area, mem, size);
		if (!ret)
			ret = new_alloc(mem, size);
	}
	return (ret);
}

void	*realloc(void *ptr, size_t size)
{
	t_area	*area;
	t_mem	*mem;

	if (!ptr)
		return (malloc(size));
	area = g_area;
	while (area)
	{
		if (area->type != empty)
		{
			mem = get_mem_in_lst(ptr, area->mem);
			if (mem)
				return (adjust_mem(area, mem, size));
		}
		area = area->next;
	}
	return (NULL);
}
