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

static void	print_mem_list(t_mem *mem, size_t max_alloc, unsigned long *total_size)
{
	size_t	n;

	n = 0;
	while (n < max_alloc)
	{
		if (mem[n].state)
		{
			print_ptr(mem[n].begin);
			print_str(" - ");
			print_ptr(mem[n].end);
			print_str(" : ");
			print_nbr(mem[n].len);
			write(1, "\n", 1);
			*total_size += (unsigned long)(mem[n].len);
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
		print_mem_list(g_malloc.tiny, MAX_TINY, &total_size);
		print_str("SMALL : ");
		print_ptr((void *)ADDR_SMALL);
		write(1, "\n", 1);
		print_mem_list(g_malloc.small, MAX_SMALL, &total_size);
		print_str("LARGE : ");
		print_ptr((void *)ADDR_LARGE);
		write(1, "\n", 1);
		print_mem_list(g_malloc.large, MAX_LARGE, &total_size);
	}
	print_str("Total : ");
	print_nbr(total_size);
	print_str(" octets\n");
}
