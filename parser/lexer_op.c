/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 08:45:59 by marvin            #+#    #+#             */
/*   Updated: 2025/12/16 17:06:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*parse_operator(char *input, int *i)
{
	if (input[*i] == '|')
		return ((*i)++, token_new(TOK_PIPE, NULL));
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
			return ((*i += 2), token_new(TOK_HEREDOC, NULL));
		return ((*i)++, token_new(TOK_REDIR_IN, NULL));
	}
	if (input[*i + 1] == '>')
		return ((*i += 2), token_new(TOK_APPEND, NULL));
	return ((*i)++, token_new(TOK_REDIR_OUT, NULL));
}
