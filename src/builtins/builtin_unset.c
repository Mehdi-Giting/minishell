/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:39:15 by marvin            #+#    #+#             */
/*   Updated: 2025/12/18 15:28:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_match(char *key, char **my_env)
{
	int	index;

	index = 0;
	while (my_env[index])
	{
		if (ft_strncmp(my_env[index], key, ft_strlen(key)) == 0)
			if (my_env[index][ft_strlen(key)] == '=')
				return (index);
		index++;
	}
	return (-1);
}

static char	**ft_tabdelete(char **my_env, int index)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (my_env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (NULL);
	i = 0;
	while (my_env[i])
	{
		if (i == index)
			i++;
		new_env[j] = ft_strdup(my_env[i]);
		j++;
		i++;
	}
	ft_free_tab(my_env);
	new_env[j] = NULL;
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
