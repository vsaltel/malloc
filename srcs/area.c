/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:34:30 by vsaltel           #+#    #+#             */
/*   Updated: 2021/04/30 17:11:13 by vsaltel          ###   ########.fr       */
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

static void	add_to_end(t_area *area)
{
	t_area		*tmp;

	if (!g_area)
		g_area = area;
	else
	{
		tmp = g_area;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = area;
	}
}

t_area	*area_init(size_t size, t_type type)
{
	t_area		*area;
	size_t		page_size;

	page_size = (size_t)getpagesize();
	if (type == large)
		size += sizeof(t_area);
	else if (type == small)
		size = (((MAX_SMALL * 100) / page_size) + 1) * page_size;
	else
		size = (((MAX_TINY * 100) / page_size) + 1) * page_size;
	area = mmap(get_addr_area(type), size,
			PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (area == MAP_FAILED)
		return (NULL);
	area->len = size;
	area->type = type;
	area->mem = NULL;
	area->next = NULL;
	add_to_end(area);
	return (area);
}
