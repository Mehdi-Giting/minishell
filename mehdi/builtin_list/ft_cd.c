/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 02:43:55 by marvin            #+#    #+#             */
/*   Updated: 2025/12/05 11:16:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_target_path(char **argv, char **my_env)
{
	char	*path;
	int		print;

	print = 0;
	if (!argv[1])
		path = ft_getenv("HOME", my_env);
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		print = 1;
		path = ft_getenv("OLDPWD", my_env);
	}
	else
		path = argv[1];
	if (!path)
	{
		perror("ft_getenv");
		return (NULL);
	}
	if (print == 1)
		ft_printf("%s\n", path);
	return (path);
}

static int	update_env_after_cd(char *old_pwd, char ***my_env)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	ft_setenv("OLDPWD", old_pwd, my_env);
	ft_setenv("PWD", cwd, my_env);
	return (0);
}

int	ft_cd(char **argv, char ***my_env)
{
	char 	*path;
	char	*old_pwd;

	path = get_target_path(argv, *my_env);
	if (!path)
		return (1);
	old_pwd = ft_getenv("PWD", *my_env);
	if (!old_pwd)
	{
		perror("ft_getenv");
		return (1);
	}
	if (chdir(path) == -1)
	{
		perror("chdir");
		return (1);
	}
	return (update_env_after_cd(old_pwd, my_env));
}

