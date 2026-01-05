/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellabiad <ellabiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:12:59 by ellabiad          #+#    #+#             */
/*   Updated: 2026/01/05 16:13:34 by ellabiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_other_heredocs(t_cmd *all_cmds, t_cmd *current)
{
	t_cmd	*tmp;
	t_redir	*redir;

	tmp = all_cmds;
	while (tmp)
	{
		if (tmp != current)
		{
			redir = tmp->redirections;
			while (redir)
			{
				if (redir->type == R_HEREDOC && redir->heredoc_fd > 2)
					close(redir->heredoc_fd);
				redir = redir->next;
			}
		}
		tmp = tmp->next;
	}
}

void	close_all_heredoc_fds(t_cmd *cmds)
{
	t_cmd	*current;
	t_redir	*redir;

	current = cmds;
	while (current)
	{
		redir = current->redirections;
		while (redir)
		{
			if (redir->type == R_HEREDOC && redir->heredoc_fd != -1)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		current = current->next;
	}
}
