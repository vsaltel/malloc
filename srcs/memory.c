/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:34:53 by vsaltel           #+#    #+#             */
/*   Updated: 2021/04/30 18:02:01 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_mem	*get_mem_in_lst(void *ptr, t_mem *mem)
{
	while (mem)
	{
		if (ptr >= (void *)mem && (char *)ptr < (char *)mem + mem->len)
			return (mem);
		mem = mem->next;
	}
	return (NULL);
}

static t_mem	*set_mem(t_area *area, size_t size, t_mem *bef, t_mem *aft)
{
	t_mem	*mem;

	if (!bef)
	{
		mem = (t_mem *)(area + 1);
		mem->len = size;
		if (aft)
			mem->next = aft;
		else
			mem->next = NULL;
		area->mem = mem;
	}
	else
	{
		mem = (t_mem *)((char *)bef + bef->len);
		mem->len = size;
		if (bef->next)
			mem->next = bef->next;
		bef->next = mem;
	}
	return (mem);
}

t_mem	*set_mem_in_area(t_area *area, size_t size)
{
	t_mem	*tmp;
	char	*area_end;

	tmp = area->mem;
	if (!tmp && (size_t)(area->len - sizeof(t_area)) >= size)
		return (set_mem(area, size, NULL, NULL));
	else if (tmp && (char *)tmp != (char *)(area + 1) && \
		(size_t)((char *)tmp - (char *)(area + 1)) >= size)
		return (set_mem(area, size, NULL, tmp));
	while (tmp)
	{
		if (!tmp->next)
		{
			area_end = (char *)area + area->len;
			if ((size_t)(area_end - ((char *)tmp + tmp->len)) >= size)
				return (set_mem(area, size, tmp, NULL));
		}
		else if (tmp->next && \
			(size_t)(((char *)tmp->next) - ((char *)tmp + tmp->len)) >= size)
			return (set_mem(area, size, tmp, NULL));
		tmp = tmp->next;
	}
	return (NULL);
}
