/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 23:09:02 by mehdi             #+#    #+#             */
/*   Updated: 2025/12/15 15:18:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_for_absolut_path(const char *cmd)
{
	return (ft_strchr(cmd, '/') != NULL);
}

static char	*resolve_path_from_env(const char *cmd)
{
	char	**path;
	char	*tmp;
	char	*final_path;
	int		i;

	i = 0;
	if (!getenv("PATH"))
		return (NULL);
	path = ft_split(getenv("PATH"), ':');
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		final_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(final_path, X_OK) == 0)
		{
			ft_free_tab(path);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	ft_free_tab(path);
	return (NULL);
}

char	*find_in_path(const char *cmd)
{
	char	*final_path;

	if (check_for_absolut_path(cmd))
	{
		if (access(cmd, X_OK) == 0)
		{
			final_path = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
			ft_strlcpy(final_path, cmd, ft_strlen(cmd) + 1);
			return (final_path);
		}
		else
		{
			ft_printf("command not found\n");
			exit(127);
		}
	}
	final_path = resolve_path_from_env(cmd);
	if (!final_path)
	{
		ft_printf("command not found\n");
		exit(127);
	}
	return (final_path);
}
