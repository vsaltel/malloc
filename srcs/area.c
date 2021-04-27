/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:34:30 by vsaltel           #+#    #+#             */
/*   Updated: 2021/04/27 14:56:22 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*get_addr_area(t_type type)
{
	if (type == empty)
		return (NULL);
	if (type == tiny)
		return ((void *)ADDR_TINY);
	if (type == small)
		return ((void *)ADDR_SMALL);
	if (type == large)
		return ((void *)ADDR_LARGE);
	return (NULL);
}

t_area	*get_area(t_area *area, t_type type)
{
	size_t			n;

	n = 0;
	while (n < NB_AREA)
	{
		if (area[n].type == type)
			return (&area[n]);
		n++;
	}
	return (NULL);
}

void	*area_alloc(t_area *area, size_t size)
{
	size_t	block_size;

	if (area->type == empty)
		return (NULL);
	if (area->type == large)
		block_size = size;
	else if (size <= g_malloc.page_size)
		block_size = g_malloc.page_size;
	else
		block_size = ((size / g_malloc.page_size) + 1) * g_malloc.page_size;
	area->ptr = mmap(get_addr_area(area->type), block_size,
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, 0, 0);
	if (area->ptr == MAP_FAILED)
		return (NULL);
	area->len = block_size;
	return (area->ptr);
}

t_area	*area_init(t_type type, size_t size)
{
	t_area		*area;
	size_t		n;

	area = get_area(g_malloc.area, empty);
	if (!area)
		return (NULL);
	area->type = type;
	area->lst = NULL;
	n = 0;
	while (n < AREA_MAX_ALLOC)
	{
		area->mem[n].state = 0;
		area->mem[n].next = NULL;
		n++;
	}
	if (!area_alloc(area, size))
		return (NULL);
	return (area);
}
