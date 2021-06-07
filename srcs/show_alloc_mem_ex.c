/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 15:00:51 by vsaltel           #+#    #+#             */
/*   Updated: 2021/06/07 15:30:16 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	hex_print(char *ptr)
{
	write(1, "\n\t", 2);
	print_ptr(ptr);
	write(1, " ", 1);
}

static void	hex_dump_mem(t_mem *mem)
{
	const char		hex[] = "0123456789ABCDEF";
	char			*ptr;
	unsigned char	block;
	unsigned char	buf[2];

	ptr = (char *)mem + sizeof(t_mem);
	hex_print(ptr);
	while (ptr < (char *)mem + mem->len)
	{
		block = *ptr;
		if (ptr != (char *)mem + sizeof(t_mem) && \
			(size_t)(ptr - (char *)mem + sizeof(t_mem)) % 16 == 0)
			hex_print(ptr);
		else if (ptr != (char *)mem + sizeof(t_mem))
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
	print_ptr((char *)mem + sizeof(t_mem));
	print_str(" - ");
	print_ptr((char *)mem + mem->len - 1);
	print_str(" : ");
	print_nbr(mem->len - sizeof(t_mem));
	hex_dump_mem(mem);
}

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
				print_mem(mem);
				*total_size += (unsigned long)(mem->len - sizeof(t_mem));
				mem = mem->next;
			}
		}
		area = area->next;
	}
}

void	show_alloc_mem_ex(void)
{
	unsigned long	total_size;

	pthread_mutex_lock(&g_mutex);
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
	pthread_mutex_unlock(&g_mutex);
}
