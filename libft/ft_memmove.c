/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:27:31 by ellabiad          #+#    #+#             */
/*   Updated: 2025/04/03 22:47:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*p_dest;
	unsigned char	*p_src;

	p_dest = (unsigned char *)dest;
	p_src = (unsigned char *)src;
	if (dest > src)
	{
		p_dest = p_dest + (n - 1);
		p_src = p_src + (n - 1);
		while (n > 0)
		{
			*p_dest = *p_src;
			p_dest--;
			p_src--;
			n--;
		}
	}
	else if (dest != src)
		ft_memcpy(dest, src, n);
	return (dest);
}
