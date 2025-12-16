/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:36:34 by marvin            #+#    #+#             */
/*   Updated: 2025/12/16 17:07:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_redir(t_token_type type)
{
    return (type == TOK_REDIR_IN
        || type == TOK_REDIR_OUT
        || type == TOK_APPEND
        || type == TOK_HEREDOC);
}

int	check_syntax(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (!token)
    	return (0);
	if (tmp->type == TOK_PIPE)
		return (ft_printf("minishell: syntax error near unexpected token `|'\n"), 2);
	while (tmp->next)
	{
		if (tmp->type == TOK_PIPE && tmp->next->type == TOK_PIPE)
			return (ft_printf("minishell: syntax error near unexpected token `|'\n"), 2);
		if (is_redir(tmp->type))
		{
			if (!tmp->next)
				return (ft_printf("minishell: syntax error near unexpected token `newline'\n"), 2);
			if (tmp->next->type == TOK_PIPE)
				return (ft_printf("minishell: syntax error near unexpected token `|'\n"), 2);
		}
		tmp = tmp->next;
	}
	if (tmp->type == TOK_PIPE)
		return (ft_printf("minishell: syntax error near unexpected token `|'\n"), 2);
	return (0);
}
