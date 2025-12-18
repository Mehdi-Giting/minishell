/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_error_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:53:57 by marvin            #+#    #+#             */
/*   Updated: 2025/12/18 16:55:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_directory_error(const char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)cmd, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	exit(126);
}

static void	print_permission_error(const char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)cmd, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	exit(126);
}

static void	print_not_found_error(const char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(127);
}

void	print_path_error_and_exit(const char *cmd)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			print_directory_error(cmd);
		else
			print_permission_error(cmd);
	}
	else
		print_not_found_error(cmd);
}
