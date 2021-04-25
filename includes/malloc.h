#ifndef MALLOC_H
# define MALLOC_H

# define NB_AREA 10
# define AREA_MAX_ALLOC 100
# define MAX_TINY 100
# define MAX_SMALL 100
# define MAX_LARGE 100
# define ADDR_TINY 0xA00000000
# define ADDR_SMALL 0xB00000000
# define ADDR_LARGE 0xC00000000

# include <sys/mman.h>
# include <stdio.h>

# include "libft.h"

typedef enum e_type
{
	empty,
	tiny,
	small,
	large
}				t_type;

typedef struct s_mem
{
	size_t			state;
	void			*begin;
	void			*end;
	size_t			len;
	struct s_mem	*next;
}				t_mem;

typedef struct s_area
{
	t_type	type;
	void	*ptr;
	size_t	len;
	t_mem	mem[AREA_MAX_ALLOC];
	t_mem	*lst;
}				t_area;

typedef struct s_malloc
{
	int		init;
	size_t	data_limit;
	size_t	page_size;
	t_area	area[NB_AREA];
}				t_malloc;

extern t_malloc	g_malloc;

/*
** srcs/malloc.c
*/

void	*malloc(size_t size);

/*
** srcs/realloc.c
*/

void	*realloc(void *ptr, size_t size);

/*
** srcs/free.c
*/

void	free(void *ptr);

/*
** srcs/show_alloc_mem.c
*/

void	show_alloc_mem(void);

/*
** srcs/malloc_utils.c
*/

void	malloc_init(void);

/*
** srcs/memory.c
*/

t_mem	*set_mem_in_area(t_area *area, t_mem *mem, size_t size);
t_mem	*get_empty_mem(t_mem *mem);
t_mem	*get_mem_in_lst(void *ptr, t_mem *lst);

/*
**	srcs/area.c
*/

void	*get_addr_area(t_type type);
void	*area_alloc(t_area *area, size_t size);
t_area	*get_area(t_area *area, t_type type);
t_area	*area_init(t_type type, size_t size);

#endif
