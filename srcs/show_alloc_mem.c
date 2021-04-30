/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:35:10 by vsaltel           #+#    #+#             */
/*   Updated: 2021/04/30 16:36:08 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	print_mem_list(t_area *area, t_type type, unsigned long *total_size)
{
	t_mem	*mem;

	while (area)
	{
		if (area->type == type)
		{
			mem = area->mem;
			while (mem)
			{
				print_ptr((char *)mem + sizeof(t_mem));
				print_str(" - ");
				print_ptr((char *)mem + mem->len);
				print_str(" : ");
				print_nbr(mem->len - sizeof(t_mem));
				write(1, "\n", 1);
				*total_size += (unsigned long)(mem->len - sizeof(t_mem));
				mem = mem->next;
			}
		}
		area = area->next;
	}
}

void	show_alloc_mem(void)
{
	unsigned long	total_size;

	total_size = 0;
	print_str("TINY : ");
	print_ptr((void *)ADDR_TINY);
	write(1, "\n", 1);
	print_mem_list(g_area, tiny, &total_size);
	print_str("SMALL : ");
	print_ptr((void *)ADDR_SMALL);
	write(1, "\n", 1);
	print_mem_list(g_area, small, &total_size);
	print_str("LARGE : ");
	print_ptr((void *)ADDR_LARGE);
	write(1, "\n", 1);
	print_mem_list(g_area, large, &total_size);
	print_str("Total : ");
	print_nbr(total_size);
	print_str(" octets\n");
}
