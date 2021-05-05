/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:34:45 by vsaltel           #+#    #+#             */
/*   Updated: 2021/04/30 16:48:08 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_area	*g_area;

static t_mem	*alloc_new_area(size_t size, t_type type)
{
	t_area	*area;

	area = area_init(size, type);
	if (!area)
		return (NULL);
	return (set_mem_in_area(area, size));
}

static t_mem	*alloc_in_area(t_area *beg, size_t size, t_type type)
{
	t_area	*area;
	t_mem	*mem;

	area = get_area(beg, size);
	if (!area)
		return (alloc_new_area(size, type));
	mem = set_mem_in_area(area, size);
	if (!mem)
		return (alloc_in_area(area->next, size, type));
	return (mem);
}

void	*malloc(size_t size)
{
	struct rlimit	rlp;
	t_mem			*ret;

	if (!size)
		return (NULL);
	getrlimit(RLIMIT_DATA, &rlp);
	size = size + sizeof(t_mem);
	if (size >= rlp.rlim_cur)
		return (NULL);
	ret = alloc_in_area(g_area, size, get_type_area(size));
	if (ret)
		return ((char *)ret + sizeof(t_mem));
	return (NULL);
}
