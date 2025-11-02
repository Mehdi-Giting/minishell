/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:57:33 by ellabiad          #+#    #+#             */
/*   Updated: 2025/04/03 22:58:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	needle;
	char	*last_occ;
	int		i;

	i = 0;
	needle = (char)c;
	last_occ = NULL;
	while (s[i])
	{
		if (s[i] == needle)
			last_occ = (char *)(s + i);
		i++;
	}
	if (s[i] == needle)
		last_occ = (char *)(s + i);
	return (last_occ);
}
