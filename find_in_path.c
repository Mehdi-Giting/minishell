/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 23:09:02 by mehdi             #+#    #+#             */
/*   Updated: 2025/11/06 00:28:51 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int	check_for_absolut_path(const char *cmd)
{
	char	frontslash;
	int		i;

	frontslash = '/';
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == frontslash)
			return (1);
		else
			i++;
	}
	return (0);
}

char	*find_in_path(const char *cmd)
{
	char	*final_path;
	char	*tmp;
	char	**path;
	int		i;

	if (check_for_absolut_path(cmd))
	{
		if (access(cmd, X_OK) == 0)
		{
			final_path = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
			ft_strlcpy(final_path, cmd, ft_strlen(cmd) + 1);
			return (final_path);
		}
		else
			return (NULL);
	}
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
		i++;
	}
	ft_free_tab(path);
	return (NULL);	
}
