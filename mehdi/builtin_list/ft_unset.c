/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:39:15 by marvin            #+#    #+#             */
/*   Updated: 2025/12/04 13:19:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_match(char **argv, char **my_env)
{
	int	index;

	index = 0;
	while (my_env[index])
	{
		if (ft_strncmp(my_env[index], argv[1], ft_strlen(argv[1])) == 0)
			if (my_env[index][ft_strlen(argv[1])] == '=')
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

int	ft_unset(char **argv, char ***my_env)
{
	int	match;

	match = find_match(argv, *my_env);
	if (match < 0)
		return (0);
	else
		*my_env = ft_tabdelete(*my_env, match);
	return (0);
}