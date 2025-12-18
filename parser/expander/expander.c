/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:08:52 by marvin            #+#    #+#             */
/*   Updated: 2025/12/18 17:56:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	expand_argv(char **argv, char **env)
{
	int		i;
	char	*expanded;

	i = 0;
	while (argv && argv[i])
	{
		expanded = expand_string(argv[i], env);
		free(argv[i]);
		argv[i] = expanded;
		i++;
	}
}

static void	expand_redirs(t_redir *r, char **env)
{
	char	*expanded;

	while (r)
	{
		expanded = expand_string(r->file, env);
		free(r->file);
		r->file = expanded;
		r = r->next;
	}
}

void	expand_cmds(t_cmd *cmds, char **env)
{
	while (cmds)
	{
		expand_argv(cmds->tokens, env);
		expand_redirs(cmds->redirections, env);
		cmds = cmds->next;
	}
}
