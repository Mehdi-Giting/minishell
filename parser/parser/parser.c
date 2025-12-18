/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:40:03 by marvin            #+#    #+#             */
/*   Updated: 2025/12/18 17:56:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redir_type	token_to_redir(t_token_type type)
{
	if (type == TOK_REDIR_IN)
		return (R_IN);
	if (type == TOK_REDIR_OUT)
		return (R_OUT);
	if (type == TOK_APPEND)
		return (R_APPEND);
	if (type == TOK_HEREDOC)
		return (R_HEREDOC);
	return (-1);
}

static void	handle_word(t_token **tok, t_arg **args)
{
	arg_add_back(args, (*tok)->value);
	*tok = (*tok)->next;
}

static void	handle_redir(t_token **tok, t_cmd *cmd)
{
	add_redirection(cmd, token_to_redir((*tok)->type),
		(*tok)->next->value);
	*tok = (*tok)->next->next;
}

static void	handle_pipe(t_token **tok, t_arg **args, t_cmd **cmd)
{
	(*cmd)->tokens = arg_list_to_argv(*args);
	*args = NULL;
	(*cmd)->next = cmd_new();
	*cmd = (*cmd)->next;
	*tok = (*tok)->next;
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd;
	t_cmd	*cmd_list;
	t_arg	*args;
	t_token	*tok;

	if (!tokens)
		return (NULL);
	tok = tokens;
	args = NULL;
	cmd = cmd_new();
	if (!cmd)
		return (NULL);
	cmd_list = cmd;
	while (tok)
	{
		if (tok->type == TOK_WORD)
			handle_word(&tok, &args);
		else if (is_redir(tok->type))
			handle_redir(&tok, cmd);
		else if (tok->type == TOK_PIPE)
			handle_pipe(&tok, &args, &cmd);
	}
	cmd->tokens = arg_list_to_argv(args);
	free_arg_list(args);
	return (cmd_list);
}
