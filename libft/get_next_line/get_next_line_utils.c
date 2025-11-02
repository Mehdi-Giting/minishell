/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:19:11 by ellabiad          #+#    #+#             */
/*   Updated: 2025/11/02 02:07:15 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_gnl_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (NULL);
}

char	*ft_gnl_strdup(char *str)
{
	int		i;
	char	*dest;

	i = 0;
	if (!str)
		return (NULL);
	dest = malloc(sizeof(char) * ft_gnl_strlen(str) + 1);
	if (!dest)
		return (NULL);
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_gnl_strlen(s))
		return (ft_gnl_strdup(""));
	if (len > ft_gnl_strlen(s + start))
		len = ft_gnl_strlen(s + start);
	dest = malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	while (i < len && s[start] != '\0')
	{
		dest[i] = s[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_gnl_strdup(s2));
	if (!s2)
		return (ft_gnl_strdup(s1));
	dest = malloc(sizeof(char) * ft_gnl_strlen(s1) + ft_gnl_strlen(s2) + 1);
	if (!dest)
		return (NULL);
	while (s1[i])
		dest[j++] = s1[i++];
	i = 0;
	while (s2[i])
		dest[j++] = s2[i++];
	dest[j] = '\0';
	free(s1);
	return (dest);
}
