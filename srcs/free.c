/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:34:39 by vsaltel           #+#    #+#             */
/*   Updated: 2021/04/29 17:40:07 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	free_area(t_area *area, t_area *bef)
{
	int		ret;
	t_area	*tmp;

	ret = 0;
	if (area->mem == NULL)
		return (ret);
	tmp = g_area;
	while (tmp)
	{
		if (tmp->type == area->type && tmp != area)
		{
			if (bef)
				bef->next = area->next;
			else
				g_area = area->next;
			ret = munmap(area, area->len);
		}
		tmp = tmp->next;
	}
	return (ret);
}

static int	free_mem(t_area *area, t_mem *mem, t_area *bef)
{
	t_mem	*tmp;

	if (area->mem == mem)
		area->mem = mem->next;
	else
	{
		tmp = area->mem;
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
	return (free_area(area, bef));
}

void	free(void *ptr)
{
	t_area	*area;
	t_area	*bef;
	t_mem	*mem;

	if (!ptr)
		return ;
	area = g_area;
	bef = NULL;
	while (area)
	{
		if (area->type != empty)
		{
			mem = get_mem_in_lst(ptr, area->mem);
			if (mem)
			{
				free_mem(area, mem, bef);
				return ;
			}
		}
		bef = area;
		area = area->next;
	}
}
