#include "malloc.h"

static void	print_ptr(void *ptr)
{
	unsigned long long	ull;
	const char			hex[] = "0123456789ABCDEF";
	char				buf[50];
	size_t				i;

	ull = (unsigned long long)ptr;
	i = 0;
	while (ull > 0)
	{
		buf[i++] = hex[ull % 16];
		ull /= 16;
	}
	buf[i] = '\0';
	write(1, "0x", 2);
	write(1, ft_strrev(buf), i);
}

static void	print_str(char *str)
{
	write(1, str, ft_strlen(str));
}

static void print_nbr(size_t n)
{
	int	tmp;

	if (n < 10)
	{
		tmp = n + 48;
		write(1, &tmp, 1);
	}
	else
	{
		print_nbr(n / 10);
		tmp = (n % 10) + 48;
		write(1, &tmp, 1);
	}
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
