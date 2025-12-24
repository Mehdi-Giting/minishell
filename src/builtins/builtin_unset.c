/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:39:15 by marvin            #+#    #+#             */
/*   Updated: 2025/12/24 11:55:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_match(char *key, char **my_env)
{
	int	index;
	int	key_len;

	index = 0;
	key_len = ft_strlen(key);
	while (my_env[index])
	{
		if (ft_strncmp(my_env[index], key, key_len) == 0)
		{
			if (my_env[index][key_len] == '=' || my_env[index][key_len] == '\0')
				return (index);
		}
		index++;
	}
	return (-1);
}

static char	**ft_tabdelete(char **my_env, int index_to_delete)
{
	char	**new_env;
	int		i;
	int		j;
	int		size;

	size = 0;
	while (my_env[size])
		size++;
	new_env = malloc(sizeof(char *) * size);
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (my_env[i])
	{
		if (i != index_to_delete)
		{
			new_env[j] = ft_strdup(my_env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	ft_free_tab(my_env);
	return (new_env);
}

int	builtin_unset(char **argv, char ***my_env)
{
	int	match;
	int	i;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		match = find_match(argv[i], *my_env);
		if (match >= 0)
			*my_env = ft_tabdelete(*my_env, match);
		i++;
	}
	return (0);
}