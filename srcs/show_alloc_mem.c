/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:35:10 by vsaltel           #+#    #+#             */
/*   Updated: 2021/04/27 15:00:26 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	print_mem_list(t_area *area, t_type type, unsigned long *total_size)
{
	size_t	n;
	t_mem	*mem;

	n = 0;
	while (n < NB_AREA)
	{
		if (area[n].type == type)
		{
			mem = area[n].lst;
			while (mem)
			{
				print_ptr(mem->begin);
				print_str(" - ");
				print_ptr(mem->end);
				print_str(" : ");
				print_nbr(mem->len);
				write(1, "\n", 1);
				*total_size += (unsigned long)(mem->len);
				mem = mem->next;
			}
		}
		n++;
	}
}

void	show_alloc_mem(void)
{
	unsigned long	total_size;

	total_size = 0;
	if (g_malloc.init)
	{
		print_str("TINY : ");
		print_ptr((void *)ADDR_TINY);
		write(1, "\n", 1);
		print_mem_list(g_malloc.area, tiny, &total_size);
		print_str("SMALL : ");
		print_ptr((void *)ADDR_SMALL);
		write(1, "\n", 1);
		print_mem_list(g_malloc.area, small, &total_size);
		print_str("LARGE : ");
		print_ptr((void *)ADDR_LARGE);
		write(1, "\n", 1);
		print_mem_list(g_malloc.area, large, &total_size);
	}
	print_str("Total : ");
	print_nbr(total_size);
	print_str(" octets\n");
}
