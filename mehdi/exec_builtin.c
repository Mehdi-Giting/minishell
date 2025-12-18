/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:11:20 by marvin            #+#    #+#             */
/*   Updated: 2025/12/18 09:21:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_builtin_with_redirections(t_cmd *cmd, char ***my_env)
{
	int		saved_stdin;
	int		saved_stdout;
	int		status;
	int		i;
	char	**saved_tokens;

	i = 0;
	while (cmd->tokens[i] && (!cmd->tokens[i][0]))
		i++;
	if (!cmd->tokens[i])
		return (0);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		if (saved_stdin != -1)
			close(saved_stdin);
		if (saved_stdout != -1)
			close(saved_stdout);
		return (1);
	}
	if (apply_redirections(cmd->redirections))
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	saved_tokens = cmd->tokens;
	cmd->tokens = &cmd->tokens[i];
	status = exec_builtin(cmd, my_env);
	cmd->tokens = saved_tokens;
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (status);
}

int	exec_builtin(t_cmd *cmd, char ***envp)
{
	if (ft_strcmp(cmd->tokens[0], "cd") == 0)
		return (ft_cd(cmd->tokens, envp));
	if (ft_strcmp(cmd->tokens[0], "echo") == 0)
		return (ft_echo(cmd->tokens));
	if (ft_strcmp(cmd->tokens[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd->tokens[0], "export") == 0 && cmd->next == NULL)
		return (ft_export(cmd->tokens, envp));
	if (ft_strcmp(cmd->tokens[0], "unset") == 0)
		return (ft_unset(cmd->tokens, envp));
	if (ft_strcmp(cmd->tokens[0], "env") == 0)
		return (ft_env(cmd->tokens, *envp));
	if (ft_strcmp(cmd->tokens[0], "exit") == 0)
		return (ft_exit(cmd->tokens));
	return (1);
}