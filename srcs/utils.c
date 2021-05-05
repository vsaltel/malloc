/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:34:30 by vsaltel           #+#    #+#             */
/*   Updated: 2021/04/30 17:11:13 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	ft_strlen(const char *s)
{
	int		len;
	char	*str;

	len = 0;
	str = (char *)s;
	if (str == NULL)
		return (0);
	while (*str++ != '\0')
		len++;
	return (len);
}

char	*ft_strrev(char *s)
{
	int		i;
	int		len;
	char	tmp;

	if (!s)
		return (NULL);
	len = ft_strlen(s) - 1;
	i = 0;
	while (i < len)
	{
		tmp = s[len];
		s[len--] = s[i];
		s[i++] = tmp;
	}
	return (s);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dst);
}
