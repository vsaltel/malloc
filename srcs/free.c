/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:34:39 by vsaltel           #+#    #+#             */
/*   Updated: 2021/04/27 14:54:22 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	free_area(t_area *area)
{
	int		ret;

	ret = munmap(area->ptr, area->len);
	area->type = empty;
	return (ret);
}

static int	free_mem(t_area *area, t_mem *mem)
{
	int		ret;
	t_mem	*tmp;

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
		ret = free_area(area);
	return (ret);
}

void	free(void *ptr)
{
	t_area	*area;
	t_mem	*mem;
	size_t	n;

	if (!ptr)
		return ;
	area = g_malloc.area;
	n = 0;
	while (n < NB_AREA)
	{
		if (area[n].type != empty)
		{
			mem = get_mem_in_lst(ptr, area[n].lst);
			if (mem)
			{
				free_mem(area + n, mem);
				return ;
			}
		}
		n++;
	}
}
