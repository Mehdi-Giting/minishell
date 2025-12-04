/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:11:20 by marvin            #+#    #+#             */
/*   Updated: 2025/12/04 13:23:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_builtin(t_cmd *cmd, char ***envp)
{
	if (ft_strcmp(cmd->tokens[0], "cd") == 0)
		return (ft_cd(cmd->tokens));
	if (ft_strcmp(cmd->tokens[0], "echo") == 0)
		return (ft_echo(cmd->tokens));
	if (ft_strcmp(cmd->tokens[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd->tokens[0], "export") == 0)
		return (ft_export(cmd->tokens, envp));
	if (ft_strcmp(cmd->tokens[0], "unset") == 0)
		return (ft_unset(cmd->tokens, envp));
	if (ft_strcmp(cmd->tokens[0], "env") == 0)
		return (ft_env(cmd->tokens, *envp));
	if (ft_strcmp(cmd->tokens[0], "exit") == 0)
		return (ft_exit());
	return (1);
}