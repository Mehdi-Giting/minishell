/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:15:26 by marvin            #+#    #+#             */
/*   Updated: 2025/12/05 11:09:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**extract_key_value(char **argv)
{
	char	**key;

	if (argv[1])
	{
		if (ft_strchr(argv[1], '='))
		{
			key = ft_split(argv[1], '=');
			return (key);
		}
	}
	key = NULL;
	return (key);
}

static int	find_key_index(char **env, char *key)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0)
			if (env[i][ft_strlen(key)] == '=')
				return (i);
		i++;
	}
	return (-1);
}

int	ft_export(char **argv, char ***my_env)
{
	char	**key;
	int		index;

	key = extract_key_value(argv);
	index = find_key_index(*my_env, key[0]);
	if (index >= 0)
		(*my_env)[index] = ft_replace_env(key[0], key[1]);
	else
		*my_env = ft_tabdup_add(*my_env, argv[1]);
	ft_free_tab(key);
	return (0);
}
