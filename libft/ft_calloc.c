/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:11:48 by ellabiad          #+#    #+#             */
/*   Updated: 2025/04/07 21:16:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "limits.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;

	if (size != 0 && count > ((size_t)-1) / size)
		return (NULL);
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	ft_memset(tmp, 0, count * size);
	return (tmp);
}
