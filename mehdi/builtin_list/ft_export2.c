/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 23:44:44 by marvin            #+#    #+#             */
/*   Updated: 2025/12/11 01:13:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	print_sorted_env(char **env)
{
    int		i;
    char	*equal_sign;

    i = 0;
	sort_env(env);
    while (env[i])
    {
        equal_sign = ft_strchr(env[i], '=');
        if (equal_sign)
        {
            write(1, "declare -x ", 11);
            write(1, env[i], equal_sign - env[i]);
            write(1, "=\"", 2);
            write(1, equal_sign + 1, ft_strlen(equal_sign + 1));
            write(1, "\"\n", 2);
        }
        else
        {
            write(1, "declare -x ", 11);
            write(1, env[i], ft_strlen(env[i]));
            write(1, "\n", 1);
        }
        i++;
    }
}

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

int	export_one_arg(char *arg, char ***my_env)
{
	char	**key_value;
	int		index;
	
	if (!is_valid_identifier(arg))
	{
		write(2, "minishell: export: `", 20);
        write(2, arg, ft_strlen(arg));
        write(2, "': not a valid identifier\n", 26);
        return (1);
	}
	key_value = extract_key_value(arg);
	if (!key_value)
		return (0);
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
