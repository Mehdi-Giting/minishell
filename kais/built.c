/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:09:21 by kfredj            #+#    #+#             */
/*   Updated: 2025/12/09 02:05:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_basic_builtins(const char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

void	is_built_in(t_cmd *cmd)
{
	if (!cmd || !cmd->tokens || !cmd->tokens[0])
		return ;
	if (check_basic_builtins(cmd->tokens[0]))
		cmd->is_builtin = 1;
	else
		cmd->is_builtin = 0;
}
