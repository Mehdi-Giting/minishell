/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:05:58 by marvin            #+#    #+#             */
/*   Updated: 2025/12/18 11:48:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_env(char **argv, char **my_env)
{
	int	i;

	i = 0;
	if (argv[1])
	{
		ft_printf("env: '%s': No such file or directory\n", argv[1]);
		return (1);
	}
	while (my_env[i])
	{
		if (ft_strchr(my_env[i], '=') && ft_strncmp(my_env[i], "_=", 2) != 0)
			ft_printf("%s\n", my_env[i]);
		i++;
	}
	return (0);
}
