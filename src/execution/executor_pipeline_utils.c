/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:00:00 by marvin            #+#    #+#             */
/*   Updated: 2025/12/18 18:00:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	wait_for_all_processes(pid_t last_pid)
{
	pid_t	wpid;
	int		status;
	int		last_status;

	last_status = 0;
	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == last_pid)
			last_status = status;
		wpid = wait(&status);
	}
	return (last_status);
}

int	wait_for_pipeline(pid_t last_pid)
{
	int	last_status;

	last_status = wait_for_all_processes(last_pid);
	setup_signals();
	return (get_signal_exit_code(last_status));
}

void	handle_parent_process(t_cmd *c, int *prev, int *pfd, pid_t *last)
{
	cleanup_parent_fds(c, prev, pfd);
	if (!c->next)
		*last = *last;
}
