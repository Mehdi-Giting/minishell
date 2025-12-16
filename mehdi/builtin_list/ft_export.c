/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:15:26 by marvin            #+#    #+#             */
/*   Updated: 2025/12/13 08:55:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	ft_export(char **argv, char ***my_env)
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
		exit_code = export_one_arg(argv[i], my_env);
		if (exit_code != 0)
			has_error = 1;
		i++;
	}
	return (has_error);
}
