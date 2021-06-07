/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:34:17 by vsaltel           #+#    #+#             */
/*   Updated: 2021/06/07 15:01:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	ft_bzero(void *s, size_t n)
{
	char		*str;

	if (n <= 0)
		return ;
	str = (char *)s;
	while (n--)
		*str++ = '\0';
}

void	*calloc(size_t count, size_t size)
{
	size_t	total;
	void	*ret;

	pthread_mutex_lock(&g_mutex);
	total = count * size;
	if (!total || total / count != size)
		return (NULL);
	ret = malloc_exec(total);
	if (ret)
		ft_bzero(ret, total);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
