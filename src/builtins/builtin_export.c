/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:15:26 by marvin            #+#    #+#             */
/*   Updated: 2025/12/24 11:57:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**extract_key_value(char *arg)
{
	char	**result;
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (NULL);
	result = malloc(sizeof(char *) * 3);
	if (!result)
		return (NULL);
	result[0] = ft_substr(arg, 0, equal_sign - arg);
	result[1] = ft_strdup(equal_sign + 1);
	result[2] = NULL;
	return (result);
}

static int	find_key_index(char **env, char *key)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0)
			if (env[i][key_len] == '=' || env[i][key_len] == '\0')
				return (i);
		i++;
	}
	return (-1);
}

static int	print_export_error(char *arg)
{
	write(2, "minishell: export: `", 20);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

static int	export_one_variable(char *arg, char ***my_env)
{
	char	**key_value;
	int		index;

	if (!is_valid_identifier(arg))
		return (print_export_error(arg));
	key_value = extract_key_value(arg);
	if (!key_value)
	{
		index = find_key_index(*my_env, arg);
		if (index < 0)
			*my_env = ft_tabdup_add(*my_env, arg);
		return (0);
	}
	index = find_key_index(*my_env, key_value[0]);
	if (index >= 0)
	{
		free((*my_env)[index]);
		(*my_env)[index] = ft_strdup(arg);
	}
	else
		*my_env = ft_tabdup_add(*my_env, arg);
	ft_free_tab(key_value);
	return (0);
}

int	builtin_export(char **argv, char ***my_env)
{
	int		i;
	int		exit_code;
	int		has_error;
	char	**my_env_cp;

	if (!argv[1])
	{
		my_env_cp = ft_tabdup(*my_env);
		print_sorted_env(my_env_cp);
		ft_free_tab(my_env_cp);
		return (0);
	}
	i = 1;
	has_error = 0;
	while (argv[i])
	{
		exit_code = export_one_variable(argv[i], my_env);
		if (exit_code != 0)
			has_error = 1;
		i++;
	}
	return (has_error);
}
