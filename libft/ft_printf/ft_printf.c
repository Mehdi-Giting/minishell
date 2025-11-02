/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:40:40 by marvin            #+#    #+#             */
/*   Updated: 2025/04/06 16:40:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_data(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int	hub(va_list ap, char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += (ft_printf_putchar(va_arg(ap, int)));
	if (c == 's')
		count += (ft_printf_putstr(va_arg(ap, char *)));
	if (c == 'd' || c == 'i')
		count += (ft_printf_putnbr(va_arg(ap, int)));
	if (c == 'p')
		count += ft_printf_putptr(va_arg(ap, void *));
	if (c == 'x' || c == 'X')
		count += ft_printf_puthex(va_arg(ap, int), c);
	if (c == 'u')
		count += ft_printf_putunsigned(va_arg(ap, unsigned int));
	if (c == '%')
		count += (ft_printf_putchar('%'));
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	ap;

	i = 0;
	count = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && is_data(format[i + 1]) == 1)
		{
			count += hub(ap, format[i + 1]);
			i = i + 2;
		}
		else
		{
			ft_printf_putchar(format[i]);
			count++;
			i++;
		}
	}
	va_end(ap);
	return (count);
}
