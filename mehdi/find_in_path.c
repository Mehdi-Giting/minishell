/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 23:09:02 by mehdi             #+#    #+#             */
/*   Updated: 2025/12/18 09:25:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_for_absolut_path(const char *cmd)
{
	return (ft_strchr(cmd, '/') != NULL);
}

static void	handle_path_error(const char *cmd)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd((char *)cmd, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			exit(126);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd((char *)cmd, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(126);
		}
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
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
	if (!path)
		return (NULL);
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
	char		*final_path;
	struct stat	path_stat;

	if (!cmd || !*cmd)
		return (NULL);
	if (check_for_absolut_path(cmd))
	{
		if (access(cmd, F_OK) == 0)
		{
			if (stat(cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd((char *)cmd, 2);
				ft_putstr_fd(": Is a directory\n", 2);
				exit(126);
			}
			if (access(cmd, X_OK) == 0)
			{
				final_path = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
				if (!final_path)
					return (NULL);
				ft_strlcpy(final_path, cmd, ft_strlen(cmd) + 1);
				return (final_path);
			}
			else
				handle_path_error(cmd);
		}
		else
			handle_path_error(cmd);
	}
	final_path = resolve_path_from_env(cmd);
	if (!final_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	return (final_path);
}
