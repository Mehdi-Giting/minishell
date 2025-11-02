/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:58:15 by ellabiad          #+#    #+#             */
/*   Updated: 2025/04/03 23:20:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*t_len_malloc(const char *s1, const char *s2)
{
	char	*tmp;

	if (s1 == NULL && s2 == NULL)
		tmp = malloc(sizeof(char) * 1);
	else if (s1 == NULL)
		tmp = malloc(sizeof(char) * (ft_strlen(s2) + 1));
	else if (s2 == NULL)
		tmp = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	else
		tmp = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*cat;

	i = 0;
	j = 0;
	cat = t_len_malloc(s1, s2);
	if (s1)
	{
		while (s1[i])
			cat[j++] = s1[i++];
	}
	i = 0;
	if (s2)
	{
		while (s2[i])
			cat[j++] = s2[i++];
	}
	cat[j] = '\0';
	return (cat);
}
