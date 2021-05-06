/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:35:03 by vsaltel           #+#    #+#             */
/*   Updated: 2021/04/29 16:56:02 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*get_mem_longer(t_area *area, t_mem *mem, size_t size)
{
	char	*mem_end;

	mem_end = (char *)mem + sizeof(t_mem) + size;
	if ((!mem->next && \
		mem_end <= (char *)(area + 1) + (area->len - sizeof(t_area))) || \
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
	free(mem);
	return (ret);
}

void	*reallocf(void *ptr, size_t size)
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
