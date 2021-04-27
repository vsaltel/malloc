/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 15:00:51 by vsaltel           #+#    #+#             */
/*   Updated: 2021/04/27 17:48:15 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	hex_print(unsigned char *ptr)
{
	write(1, "\n\t", 2);
	print_ptr(ptr);
	write(1, " ", 1);
}

static void	hex_dump_mem(t_mem *mem)
{
	const char		hex[] = "0123456789ABCDEF";
	unsigned char	*ptr;
	unsigned char	block;
	char			buf[2];

	ptr = (unsigned char *)mem->begin;
	hex_print(ptr);
	while (ptr < (unsigned char *)mem->end)
	{
		block = *ptr;
		if (ptr != mem->begin &&
			(size_t)(ptr - (unsigned char *)mem->begin) % 16 == 0)
			hex_print(ptr);
		else if (ptr != (unsigned char *)mem->begin)
			write(1, " ", 1);
		buf[0] = hex[(block / 16) % 16];
		buf[1] = hex[block % 16];
		write(1, buf, 2);
		ptr += 1;
	}
	write(1, "\n", 1);
}

static void	print_mem(t_mem *mem)
{
	print_ptr(mem->begin);
	print_str(" - ");
	print_ptr(mem->end);
	print_str(" : ");
	print_nbr(mem->len);
	hex_dump_mem(mem);
}

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
				print_mem(mem);
				*total_size += (unsigned long)(mem->len);
				mem = mem->next;
			}
		}
		n++;
	}
}

void	show_alloc_mem_ex(void)
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
