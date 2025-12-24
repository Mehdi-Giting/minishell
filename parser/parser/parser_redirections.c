/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:53:00 by marvin            #+#    #+#             */
/*   Updated: 2025/12/24 13:35:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	has_quotes(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static t_redir	*redir_new(t_redir_type type, char *file)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = type;
	new->file = ft_strdup(file);
	if (!new->file)
	{
		free(new);
		return (NULL);
	}
	new->quoted = 0;
	new->next = NULL;
	new->heredoc_fd = -1;
	return (new);
}

void	add_redirection(t_cmd *cmd, t_redir_type type, char *file)
{
	t_redir	*new;
	t_redir	*tmp;

	new = redir_new(type, file);
	if (!new)
		return ;
	if (type == R_HEREDOC && has_quotes(file))
		new->quoted = 1;
	if (!cmd->redirections)
	{
		cmd->redirections = new;
		return ;
	}
	tmp = cmd->redirections;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
