/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:36:34 by marvin            #+#    #+#             */
/*   Updated: 2025/12/18 18:10:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redir(t_token_type type)
{
	return (type == TOK_REDIR_IN
		|| type == TOK_REDIR_OUT
		|| type == TOK_APPEND
		|| type == TOK_HEREDOC);
}

static int	print_pipe_error(void)
{
	ft_printf("minishell: syntax error near unexpected token `|'\n");
	return (2);
}

static int	print_newline_error(void)
{
	ft_printf("minishell: syntax error near unexpected token `newline'\n");
	return (2);
}

int	check_syntax(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (!token)
		return (0);
	if (tmp->type == TOK_PIPE)
		return (print_pipe_error());
	while (tmp->next)
	{
		if (tmp->type == TOK_PIPE && tmp->next->type == TOK_PIPE)
			return (print_pipe_error());
		if (is_redir(tmp->type))
		{
			if (!tmp->next)
				return (print_newline_error());
			if (tmp->next->type == TOK_PIPE)
				return (print_pipe_error());
		}
		tmp = tmp->next;
	}
	if (tmp->type == TOK_PIPE)
		return (print_pipe_error());
	return (0);
}
