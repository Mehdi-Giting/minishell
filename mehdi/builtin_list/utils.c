/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 04:14:24 by marvin            #+#    #+#             */
/*   Updated: 2025/12/05 11:13:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_replace_env(const char *key, const char *value)
{
	char	*key_eq;
	char	*joined;

	key_eq = ft_strjoin(key, "=");
	if (!value)
		return (key_eq);
	joined = ft_strjoin(key_eq, value);
	free(key_eq);
	return (joined);
}

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

char	*ft_getenv(const char *key, char **my_env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (my_env[i])
	{
		if (ft_strncmp(my_env[i], key, len) == 0)
			if (my_env[i][len] == '=')
				return (my_env[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	ft_setenv(char *key, char *value, char ***my_env)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = ft_strlen(key);
	new = ft_replace_env(key, value);
	if (!key || !value || !my_env || !*my_env)
    	return ;
	while ((*my_env)[i])
	{
		if (ft_strncmp((*my_env)[i], key, len) == 0)
			if ((*my_env)[i][len] == '=')
			{
				free((*my_env)[i]);
				(*my_env)[i] = new;
				return ;
			}
		i++;
	}
	*my_env = ft_tabdup_add(*my_env, ft_replace_env(key, value));
	free(new);
}