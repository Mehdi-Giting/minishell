/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:05:58 by marvin            #+#    #+#             */
/*   Updated: 2025/12/04 00:12:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(char **argv, char **envp)
{
	int	i;

	i = 0;
	if (argv[1])
	{
		ft_printf("env: '%s': No such file or directory\n", argv[1]);
		return (1);
	}
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			ft_printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}