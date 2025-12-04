/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:15:26 by marvin            #+#    #+#             */
/*   Updated: 2025/12/04 02:59:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_export(char **argv, char **envp)
{
	char	**key;
	int		i;
	int		exist_in_env;

	i = 0;
	exist_in_env = 0;
	if (argv[1])
	{
		if (ft_strchr(argv[1], '='))
			key = ft_split(argv[1], '=');
	}
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key[0], ft_strlen(key[0])) == 0)
			if (envp[i][ft_strlen(key[0])] == '=')
				exist_in_env = 1;
		i++;
	}
	ft_free_tab(key);
	return (0);
}
