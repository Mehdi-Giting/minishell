/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:26:18 by ellabiad          #+#    #+#             */
/*   Updated: 2025/04/03 22:45:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p_s;
	unsigned char	occ;
	size_t			i;

	i = 0;
	p_s = (unsigned char *)s;
	occ = (unsigned char)c;
	while (i < n)
	{
		if (p_s[i] == occ)
			return ((void *)(p_s + i));
		i++;
	}
	return (NULL);
}
