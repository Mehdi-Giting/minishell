/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:37:09 by marvin            #+#    #+#             */
/*   Updated: 2025/12/13 09:39:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_last_exit_code = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_signals(void)
{
    signal(SIGINT, SIG_IGN);   // Ignore Ctrl+C
    signal(SIGQUIT, SIG_IGN);  // Ignore ctrl+'\'
}

void	default_signals(void)
{
    signal(SIGINT, SIG_DFL);   // Comportement par défaut
    signal(SIGQUIT, SIG_DFL);  // Comportement par défaut
}

int	get_signal_exit_code(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}