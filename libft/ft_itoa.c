/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:46:16 by marvin            #+#    #+#             */
/*   Updated: 2025/04/03 12:46:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_char(int n)
{
	int		i;
	long	ln;

	i = 0;
	ln = (long)n;
	if (ln < 0)
	{
		ln = ln * -1;
		i++;
	}
	while (ln > 0)
	{
		ln = ln / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa_malloc(int n)
{
	char	*dest;

	dest = malloc(sizeof(char) * (ft_count_char(n) + 1));
	if (!dest)
		return (NULL);
	return (dest);
}

char	*ft_itoa(int n)
{
	int		i;
	long	ln;
	char	*dest;

	if (n == 0)
		return (ft_strdup("0"));
	i = ft_count_char(n) - 1;
	ln = (long)n;
	dest = ft_itoa_malloc(n);
	if (!dest)
		return (NULL);
	if (n < 0)
	{
		dest[0] = '-';
		ln = ln * -1;
	}
	dest[i + 1] = '\0';
	while (ln > 0)
	{
		dest[i] = ln % 10 + '0';
		ln = ln / 10;
		i--;
	}
	return (dest);
}
