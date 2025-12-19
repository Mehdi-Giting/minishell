/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:11:20 by marvin            #+#    #+#             */
/*   Updated: 2025/12/18 19:30:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Dispatch to appropriate builtin function
 */
int	dispatch_builtin(t_cmd *cmd, char ***envp)
{
	if (ft_strcmp(cmd->tokens[0], "cd") == 0)
		return (builtin_cd(cmd->tokens, envp));
	if (ft_strcmp(cmd->tokens[0], "echo") == 0)
		return (builtin_echo(cmd->tokens));
	if (ft_strcmp(cmd->tokens[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->tokens[0], "export") == 0 && cmd->next == NULL)
		return (builtin_export(cmd->tokens, envp));
	if (ft_strcmp(cmd->tokens[0], "unset") == 0)
		return (builtin_unset(cmd->tokens, envp));
	if (ft_strcmp(cmd->tokens[0], "env") == 0)
		return (builtin_env(cmd->tokens, *envp));
	if (ft_strcmp(cmd->tokens[0], "exit") == 0)
		return (builtin_exit(cmd->tokens));
	return (1);
}

/*
 * Save file descriptors before applying redirections
 */
static int	save_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin == -1 || *saved_stdout == -1)
	{
		if (*saved_stdin != -1)
			close(*saved_stdin);
		if (*saved_stdout != -1)
			close(*saved_stdout);
		return (1);
	}
	return (0);
}

/*
 * Restore file descriptors after builtin execution
 */
static void	restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

/*
 * Execute builtin with proper redirection handling
 */
int	execute_builtin_with_redirections(t_cmd *cmd, char ***my_env)
{
	int		saved_stdin;
	int		saved_stdout;
	int		status;
	int		i;
	char	**saved_tokens;

	i = skip_empty_tokens(cmd->tokens);
	if (!cmd->tokens[i])
		return (0);
	if (save_fds(&saved_stdin, &saved_stdout))
		return (1);
	if (apply_redirections(cmd->redirections, *my_env))
	{
		restore_fds(saved_stdin, saved_stdout);
		return (1);
	}
	saved_tokens = cmd->tokens;
	cmd->tokens = &cmd->tokens[i];
	status = dispatch_builtin(cmd, my_env);
	cmd->tokens = saved_tokens;
	restore_fds(saved_stdin, saved_stdout);
	return (status);
}
