#ifndef MALLOC_H
# define MALLOC_H

# define MAX_TINY 100
# define MAX_SMALL 100
# define MAX_LARGE 100
# define ADDR_TINY 0xA0000000
# define ADDR_SMALL 0xB0000000
# define ADDR_LARGE 0xC0000000

# include <sys/mman.h>
# include <stdio.h>

# include "libft.h"
//# include "/Users/valentin/Desktop/42/malloc/libft/includes/libft.h"


typedef struct s_mem
{
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
	size_t	tiny_alloc;
	t_mem	small[MAX_SMALL];
	size_t	small_alloc;
	t_mem	large[MAX_LARGE];
	size_t	large_alloc;
}				t_malloc;

extern t_malloc	g_malloc;

void	show_alloc_mem(void);
void	*malloc(size_t size);

#endif
