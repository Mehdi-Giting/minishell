/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:44:57 by marvin            #+#    #+#             */
/*   Updated: 2025/04/06 16:44:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printf_puthex(unsigned int n, const char format)
{
	int		count;
	char	*tab;

	count = 0;
	if (format == 'x')
		tab = "0123456789abcdef";
	else
		tab = "0123456789ABCDEF";
	if (n == 0)
		return (count += ft_printf_putchar('0'));
	if (n >= 16)
	{
		count += ft_printf_puthex(n / 16, format);
		count += ft_printf_puthex(n % 16, format);
	}
	else
		count += ft_printf_putchar(tab[n]);
	return (count);
}

int	ft_printf_ptoh(unsigned long addr, char *tab)
{
	int	count;

	count = 0;
	if (addr > 15)
		count += ft_printf_ptoh(addr / 16, tab);
	count += ft_printf_putchar(tab[addr % 16]);
	return (count);
}

int	ft_printf_putptr(void *ptr)
{
	int				count;
	unsigned long	addr;
	char			*tab;

	count = 0;
	addr = (unsigned long)ptr;
	tab = "0123456789abcdef";
	if (ptr == NULL)
		return (count += ft_printf_putstr("(nil)"));
	count += ft_printf_putstr("0x");
	if (addr == 0)
		count += ft_printf_putchar('0');
	else
		count += ft_printf_ptoh(addr, tab);
	return (count);
}
