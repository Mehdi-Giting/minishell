/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:53:00 by marvin            #+#    #+#             */
/*   Updated: 2025/12/18 17:56:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	new->next = NULL;
	return (new);
}

void	add_redirection(t_cmd *cmd, t_redir_type type, char *file)
{
	t_redir	*new;
	t_redir	*tmp;

	new = redir_new(type, file);
	if (!new)
		return ;
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
