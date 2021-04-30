/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:33:51 by vsaltel           #+#    #+#             */
/*   Updated: 2021/04/30 16:57:55 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define NB_AREA 10
# define AREA_MAX_ALLOC 100
# define MAX_TINY 128
# define MAX_SMALL 1024
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
	size_t			len;
	struct s_mem	*next;
}				t_mem;

typedef struct s_area
{
	t_type	type;
	char	*ptr;
	size_t	len;
	t_mem	*mem;
	struct s_area	*next;
}				t_area;

extern t_area	*g_area;

/*
** srcs/malloc.c
*/

void	*malloc(size_t size);

/*
** srcs/realloc.c
*/

void	*calloc(size_t count, size_t size);

/*
** srcs/realloc.c
*/

void	*realloc(void *ptr, size_t size);

/*
** srcs/realloc.c
*/

void	*reallocf(void *ptr, size_t size);

/*
** srcs/free.c
*/

void	free(void *ptr);

/*
** srcs/show_alloc_mem.c
*/

void	show_alloc_mem(void);

/*
** srcs/show_alloc_mem_ex.c
*/

void	show_alloc_mem_ex(void);

/*
** srcs/memory.c
*/

t_mem	*get_mem_in_lst(void *ptr, t_mem *lst);
t_mem	*set_mem_in_area(t_area *area, size_t size);

/*
**	srcs/area.c
*/

void	*get_addr_area(t_type type);
t_area	*get_area(t_area *area, size_t size);
t_area	*area_init(size_t size, t_type type);
t_type	get_type_area(size_t size);

/*
**	srcs/print.c
*/

void	print_ptr(void *ptr);
void	print_str(char *str);
void	print_nbr(size_t n);

#endif
