#include "malloc.h"

static void	print_mem_list(t_mem *mem,size_t nb_alloc, size_t max_alloc, unsigned long *total_size)
{
	size_t	n;

	n = 0;
	while (n < nb_alloc && n < max_alloc)
	{
		ft_printf("%p - %p : %zu octets\n", mem[n].begin, mem[n].end, mem[n].len);
		*total_size += (unsigned long)(mem[n].len);
		n++;
	}
}

void	show_alloc_mem(void)
{
	unsigned long	total_size;	

	total_size = 0;
	if (g_malloc.init)
	{
		if (g_malloc.tiny_alloc)
		{
			ft_printf("TINY :\n");
			print_mem_list(g_malloc.tiny, g_malloc.tiny_alloc, MAX_TINY, &total_size);
		}
		if (g_malloc.small_alloc)
		{
			ft_printf("SMALL :\n");
			print_mem_list(g_malloc.small, g_malloc.small_alloc, MAX_SMALL, &total_size);
		}
		if (g_malloc.large_alloc)
		{
			ft_printf("LARGE :\n");
			print_mem_list(g_malloc.large, g_malloc.large_alloc, MAX_LARGE, &total_size);
		}
	}
	ft_printf("Total : %lu octets\n", total_size);
}
