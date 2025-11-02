/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:05:06 by marvin            #+#    #+#             */
/*   Updated: 2025/04/03 22:49:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	ln;

	ln = (long)n;
	if (ln < 0)
	{
		ft_putchar_fd('-', fd);
		ln = ln * -1;
	}
	if (ln > 9)
	{
		ft_putnbr_fd((ln / 10), fd);
		ft_putnbr_fd((ln % 10), fd);
	}
	else
		ft_putchar_fd((ln % 10) + '0', fd);
}
