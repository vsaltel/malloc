/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:57:12 by vsaltel           #+#    #+#             */
/*   Updated: 2021/04/27 15:53:57 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_ptr(void *ptr)
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

void	print_str(char *str)
{
	write(1, str, ft_strlen(str));
}

void	print_nbr(size_t n)
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
