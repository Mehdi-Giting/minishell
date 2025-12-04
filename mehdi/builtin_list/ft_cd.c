/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 02:43:55 by marvin            #+#    #+#             */
/*   Updated: 2025/12/03 23:57:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_target_path(char **argv)
{
	char	*path;
	int		print;

	print = 0;
	if (!argv[1])
		path = getenv("HOME");
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		print = 1;
		path = getenv("OLDPWD");
	}
	else
		path = argv[1];
	if (!path)
	{
		perror("getenv");
		return (NULL);
	}
	if (print == 1)
		ft_printf("%s\n", path);
	return (path);
}

static int	update_env_after_cd(char *old_pwd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	setenv("OLDPWD", old_pwd, 1);
	setenv("PWD", cwd, 1);
	return (0);
}

int	ft_cd(char **argv)
{
	char 	*path;
	char	*old_pwd;

	path = get_target_path(argv);
	if (!path)
		return (1);
	old_pwd = getenv("PWD");
	if (!old_pwd)
	{
		perror("getenv");
		return (1);
	}
	if (chdir(path) == -1)
	{
		perror("chdir");
		return (1);
	}
	return (update_env_after_cd(old_pwd));
}

