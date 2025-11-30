/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:14:45 by kfredj            #+#    #+#             */
/*   Updated: 2025/11/30 16:47:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	if_redir(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (strcmp(&line[i], ">") == 0 || strcmp(&line[i], ">>") == 0
			|| strcmp(&line[i], "<") == 0 || strcmp(&line[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}
int	is_redirection(const char *token)
{
	if (strcmp(token, ">") == 0 || strcmp(token, ">>") == 0 || strcmp(token,
			"<") == 0 || strcmp(token, "<<") == 0)
		return (1);
	return (0);
}
static void	set_redir_type(t_redir *redir, char *token)
{
	if (strcmp(token, ">") == 0)
		redir->type = R_OUT;
	else if (strcmp(token, ">>") == 0)
		redir->type = R_APPEND;
	else if (strcmp(token, "<") == 0)
		redir->type = R_IN;
	else if (strcmp(token, "<<") == 0)
		redir->type = R_HEREDOC;
}

void	redir_finder(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->tokens[i])
	{
		if (is_redirection(cmd->tokens[i]))
		{
			printf("Redirection found: %s\n", cmd->tokens[i]);
			cmd->redirections = malloc(sizeof(t_redir));
			if (!cmd->redirections)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			set_redir_type(cmd->redirections, cmd->tokens[i]);
			if (cmd->tokens[i + 1])
				cmd->redirections->file = cmd->tokens[i + 1];
			else
				cmd->redirections->file = NULL;
		}
		i++;
	}
}
