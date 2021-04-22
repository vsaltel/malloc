#ifndef MALLOC_H
# define MALLOC_H

# define MAX_TINY 100
# define MAX_SMALL 100
# define MAX_LARGE 100
# define ADDR_TINY 0xA00000000
# define ADDR_SMALL 0xB00000000
# define ADDR_LARGE 0xC00000000

# include <sys/mman.h>
# include <stdio.h>

# include "libft.h"

typedef struct s_mem
{
	size_t	state;
	void	*begin;
	void	*end;
	size_t	len;
}				t_mem;

typedef struct s_malloc
{
	int		init;
	size_t	data_limit;
	size_t	page_size;

	t_mem	tiny[MAX_TINY];
	t_mem	small[MAX_SMALL];
	t_mem	large[MAX_LARGE];
}				t_malloc;

extern t_malloc	g_malloc;

void	show_alloc_mem(void);
void	*malloc(size_t size);

#endif
