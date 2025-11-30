/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:09:21 by kfredj            #+#    #+#             */
/*   Updated: 2025/11/30 16:46:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_basic_builtins(const char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "alias") == 0
		|| ft_strcmp(cmd, "bg") == 0 || ft_strcmp(cmd, "bind") == 0
		|| ft_strcmp(cmd, "break") == 0 || ft_strcmp(cmd, "builtin") == 0
		|| ft_strcmp(cmd, "caller") == 0 || ft_strcmp(cmd, "command") == 0)
		return (1);
	return (0);
}

static int	check_comp_builtins(const char *cmd)
{
	if (ft_strcmp(cmd, "compgen") == 0 || ft_strcmp(cmd, "complete") == 0
		|| ft_strcmp(cmd, "compopt") == 0 || ft_strcmp(cmd, "continue") == 0
		|| ft_strcmp(cmd, "declare") == 0 || ft_strcmp(cmd, "dirs") == 0
		|| ft_strcmp(cmd, "disown") == 0 || ft_strcmp(cmd, "enable") == 0
		|| ft_strcmp(cmd, "eval") == 0 || ft_strcmp(cmd, "exec") == 0
		|| ft_strcmp(cmd, "false") == 0 || ft_strcmp(cmd, "fc") == 0
		|| ft_strcmp(cmd, "fg") == 0 || ft_strcmp(cmd, "getopts") == 0)
		return (1);
	return (0);
}

static int	check_advanced_builtins(const char *cmd)
{
	if (ft_strcmp(cmd, "hash") == 0 || ft_strcmp(cmd, "help") == 0
		|| ft_strcmp(cmd, "history") == 0 || ft_strcmp(cmd, "jobs") == 0
		|| ft_strcmp(cmd, "kill") == 0 || ft_strcmp(cmd, "let") == 0
		|| ft_strcmp(cmd, "local") == 0 || ft_strcmp(cmd, "logout") == 0
		|| ft_strcmp(cmd, "mapfile") == 0 || ft_strcmp(cmd, "popd") == 0
		|| ft_strcmp(cmd, "printf") == 0 || ft_strcmp(cmd, "pushd") == 0
		|| ft_strcmp(cmd, "read") == 0 || ft_strcmp(cmd, "readarray") == 0)
		return (1);
	return (0);
}

static int	check_system_builtins(const char *cmd)
{
	if (ft_strcmp(cmd, "readonly") == 0 || ft_strcmp(cmd, "return") == 0
		|| ft_strcmp(cmd, "set") == 0 || ft_strcmp(cmd, "shift") == 0
		|| ft_strcmp(cmd, "shopt") == 0 || ft_strcmp(cmd, "source") == 0
		|| ft_strcmp(cmd, "suspend") == 0 || ft_strcmp(cmd, "test") == 0
		|| ft_strcmp(cmd, "times") == 0 || ft_strcmp(cmd, "trap") == 0
		|| ft_strcmp(cmd, "true") == 0 || ft_strcmp(cmd, "type") == 0
		|| ft_strcmp(cmd, "typeset") == 0 || ft_strcmp(cmd, "ulimit") == 0
		|| ft_strcmp(cmd, "umask") == 0 || ft_strcmp(cmd, "unalias") == 0
		|| ft_strcmp(cmd, "wait") == 0)
		return (1);
	return (0);
}

void	is_built_in(t_cmd *cmd)
{
	if (!cmd || !cmd->tokens || !cmd->tokens[0])
		return ;
	if (check_basic_builtins(cmd->tokens[0])
		|| check_comp_builtins(cmd->tokens[0])
		|| check_advanced_builtins(cmd->tokens[0])
		|| check_system_builtins(cmd->tokens[0]))
		cmd->is_builtin = 1;
	else
		cmd->is_builtin = 0;
}
