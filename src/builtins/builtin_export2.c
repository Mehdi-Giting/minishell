/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:50:22 by marvin            #+#    #+#             */
/*   Updated: 2025/12/18 15:54:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Check if identifier is valid for export
 * Must start with letter or underscore, followed by alphanumeric or underscore
 */
int	is_valid_identifier(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

/*
 * Bubble sort environment variables
 */
void	sort_env(char **env)
{
	int		i;
	int		sorted;
	char	*tmp;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (env[i] && env[i + 1])
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}

/*
 * Print environment variable in export format
 */
void	print_export_var(char *env_var)
{
	char	*equal_sign;

	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign)
	{
		write(1, "declare -x ", 11);
		write(1, env_var, equal_sign - env_var);
		write(1, "=\"", 2);
		write(1, equal_sign + 1, ft_strlen(equal_sign + 1));
		write(1, "\"\n", 2);
	}
	else
	{
		write(1, "declare -x ", 11);
		write(1, env_var, ft_strlen(env_var));
		write(1, "\n", 1);
	}
}

/*
 * Print all environment variables in sorted export format
 */
void	print_sorted_env(char **env)
{
	int	i;

	i = 0;
	sort_env(env);
	while (env[i])
	{
		print_export_var(env[i]);
		i++;
	}
}
