/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:41:14 by ellabiad          #+#    #+#             */
/*   Updated: 2025/04/03 22:51:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	needle;
	int				i;

	i = 0;
	needle = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == needle)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == needle)
		return ((char *)s + i);
	return (NULL);
}
