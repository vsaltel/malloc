/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:34:17 by vsaltel           #+#    #+#             */
/*   Updated: 2021/04/27 14:48:06 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
	ft_bzero(mem->begin, size);
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
	ft_bzero(mem->begin, size);
	return (mem->begin);
}

void	*calloc(size_t count, size_t size)
{
	if (!g_malloc.init)
		malloc_init();
	size = size * count;
	if (size > g_malloc.data_limit)
		return (NULL);
	if (size > g_malloc.page_size * 3)
		return (alloc_in_area(size, large));
	if (size > g_malloc.page_size / 3)
		return (alloc_in_area(size, small));
	return (alloc_in_area(size, tiny));
}
