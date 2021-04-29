/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:34:30 by vsaltel           #+#    #+#             */
/*   Updated: 2021/04/29 17:37:58 by vsaltel          ###   ########.fr       */
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

t_type	get_type_area(size_t size)
{
	if (size <= MAX_TINY)
		return (tiny);
	else if (size <= MAX_SMALL)
		return (small);
	return (large);
}

t_area	*get_area(t_area *area, size_t size)
{
	t_type	type;

	type = get_type_area(size);
	while (area)
	{
		if (area->type == type)
			return (area);
		area = area->next;
	}
	return (NULL);
}

t_area	*area_init(size_t size, t_type type)
{
	t_area		*area;
	
	area = mmap(get_addr_area(type), size,
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, 0, 0);
	if (area->ptr == MAP_FAILED)
		return (NULL);
	area->ptr = (t_mem *)(area + sizeof(t_area));
	area->len = size;
	area->type = type;
	area->mem = NULL;
	area->next = g_area;
	g_area = area;
	return (area);
}
