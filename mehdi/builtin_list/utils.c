/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 04:14:24 by marvin            #+#    #+#             */
/*   Updated: 2025/12/04 06:29:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_tabdup(char **my_env)
{
	char	**my_new_env;
	int		i;

	i = 0;
	while (my_env[i])
		i++;
	my_new_env = malloc(sizeof(char *) * (i + 1));
	if (!my_new_env)
		return (NULL);
	i = 0;
	while (my_env[i])
	{
		my_new_env[i] = ft_strdup(my_env[i]);
		i++;
	}
	my_new_env[i] = NULL;
	return (my_new_env);
}

char	**ft_tabdup_add(char **my_env, const char *new_key)
{
	char	**my_new_env;
	int		i;

	i = 0;
	while (my_env[i])
		i++;
	my_new_env = malloc(sizeof(char *) * (i + 2));
	if (!my_new_env)
		return (NULL);
	i = 0;
	while (my_env[i])
	{
		my_new_env[i] = ft_strdup(my_env[i]);
		i++;
	}
	my_new_env[i] = ft_strdup(new_key);
	my_new_env[i + 1] = NULL;
	ft_free_tab(my_env);
	return (my_new_env);
}
