/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 23:09:02 by mehdi             #+#    #+#             */
/*   Updated: 2025/12/18 16:54:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Check if command contains a slash (absolute or relative path)
 */
static int	is_path_command(const char *cmd)
{
	return (ft_strchr(cmd, '/') != NULL);
}

/*
 * Resolve path from PATH environment variable
 */
static char	*search_in_path_env(const char *cmd)
{
	char	**path_dirs;
	char	*tmp;
	char	*full_path;
	int		i;

	if (!getenv("PATH"))
		return (NULL);
	path_dirs = ft_split(getenv("PATH"), ':');
	if (!path_dirs)
		return (NULL);
	i = 0;
	while (path_dirs[i])
	{
		tmp = ft_strjoin(path_dirs[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_tab(path_dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (ft_free_tab(path_dirs), NULL);
}

/*
 * Handle absolute or relative path resolution
 */
static char	*resolve_absolute_path(const char *cmd)
{
	struct stat	path_stat;
	char		*final_path;

	if (access(cmd, F_OK) != 0)
		print_path_error_and_exit(cmd);
	if (stat(cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	if (access(cmd, X_OK) != 0)
		print_path_error_and_exit(cmd);
	final_path = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	if (!final_path)
		return (NULL);
	ft_strlcpy(final_path, cmd, ft_strlen(cmd) + 1);
	return (final_path);
}

/*
 * Main path resolution function
 * Returns executable path or exits with error
 */
char	*resolve_command_path(const char *cmd)
{
	char	*final_path;

	if (!cmd || !*cmd)
		return (NULL);
	if (is_path_command(cmd))
		return (resolve_absolute_path(cmd));
	final_path = search_in_path_env(cmd);
	if (!final_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	return (final_path);
}
