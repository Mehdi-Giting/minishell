/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 23:05:58 by marvin            #+#    #+#             */
/*   Updated: 2025/12/05 06:59:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_numeric_arg(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}

int	ft_exit(char **argv)
{
	ft_printf("exit\n");
	if (!argv[1])
	{
		ft_printf("%s\n", argv[0]);
		exit(0);
	}
	else if (argv[2])
	{
		ft_printf("exit: too many arguments\n");
		return (1);
	}
	else
	{
		if (is_numeric_arg(argv[1]))
		{
			ft_printf("exit: %d\n", ft_atoi(argv[1]) % 256);
			exit(ft_atoi(argv[1]) % 256);
		}
		else
		{
			ft_printf("minishell: ");
			ft_printf("exit: %s: numeric argument required\n", argv[1]);
			exit(2);
		}
	}
}
