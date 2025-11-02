/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:33:30 by marvin            #+#    #+#             */
/*   Updated: 2025/04/07 22:42:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	if (!s1)
		return (NULL);
	if (*s1 == '\0')
		return (ft_strdup(""));
	if (!set || *set == '\0')
		return (ft_strdup(s1));
	j = ft_strlen(s1) - 1;
	while (is_in_set(s1[i], set) == 1)
		i++;
	while (is_in_set(s1[j], set) == 1)
		j--;
	if (i > j)
		return (ft_strdup(""));
	dest = ft_substr(s1, i, j - i + 1);
	return (dest);
}
