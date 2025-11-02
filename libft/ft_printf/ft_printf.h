/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:58:29 by marvin            #+#    #+#             */
/*   Updated: 2025/04/06 13:58:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int		ft_printf(const char *format, ...);
int		ft_printf_putchar(char c);
int		ft_printf_putstr(char *s);
int		ft_printf_putnbr(int n);
int		ft_printf_putunsigned(unsigned int n);
int		ft_printf_puthex(unsigned int n, const char format);
int		ft_printf_putptr(void *ptr);

#endif