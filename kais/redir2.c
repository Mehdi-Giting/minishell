/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:59:53 by kfredj            #+#    #+#             */
/*   Updated: 2025/11/30 16:46:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_redir	*new_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	redir->file = NULL;
	redir->next = NULL;
	redir->type = R_IN;
	return (redir);
}

static void	add_redir_to_cmd(t_cmd *cmd, t_redir *new)
{
	t_redir	*tmp;

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

static int	get_redir_type(char *token, int *i, t_redir *redir)
{
	if (token[*i] == '>')
	{
		if (token[*i + 1] == '>')
		{
			redir->type = R_APPEND;
			*i += 2;
		}
		else
		{
			redir->type = R_OUT;
			*i += 1;
		}
	}
	else if (token[*i] == '<')
	{
		if (token[*i + 1] == '<')
		{
			redir->type = R_HEREDOC;
			*i += 2;
		}
		else
		{
			redir->type = R_IN;
			*i += 1;
		}
	}
	return (*i);
}

static char	*extract_filename(char *token, int *i)
{
	int		start;
	char	*filename;

	while (token[*i] == ' ')
		(*i)++;
	start = *i;
	while (token[*i] && token[*i] != ' ' && token[*i] != '>'
		&& token[*i] != '<')
		(*i)++;
	filename = ft_substr(token, start, *i - start);
	return (filename);
}

char	*token_cleaner(char *token, t_cmd *cmd)
{
	char	*clean;
	t_redir	*redir;
	int		i;
	int		j;

	clean = malloc(ft_strlen(token) + 1);
	if (!clean)
		return (NULL);
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '>' || token[i] == '<')
		{
			redir = new_redir();
			get_redir_type(token, &i, redir);
			redir->file = extract_filename(token, &i);
			add_redir_to_cmd(cmd, redir);
		}
		else
			clean[j++] = token[i++];
	}
	clean[j] = '\0';
	free(token);
	return (clean);
}
