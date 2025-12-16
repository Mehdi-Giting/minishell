/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 02:07:41 by marvin            #+#    #+#             */
/*   Updated: 2025/12/15 14:30:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_for_n(char *argv)
{
	int	i;

	i = 0;
	if (argv[i] == '-')
		i++;
	else
		return (0);
	while (argv[i] == 'n')
		i++;
	if (argv[i] != '\0')
		return (0);
	return (1);
}

int	ft_echo(char **argv)
{
	int		i;
	int		new_line;

	i = 1;
	new_line = 1;
	while (check_for_n(argv[i]))
	{
		new_line = 0;
		i++;
	}
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1])
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
	return (0);
}