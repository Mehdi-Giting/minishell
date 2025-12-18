/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 08:44:09 by marvin            #+#    #+#             */
/*   Updated: 2025/12/18 17:56:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	add_next_token(t_token **tokens, char *input, int *i)
{
	t_token	*new;

	if (is_operator_char(input[*i]))
		new = parse_operator(input, i);
	else
		new = parse_word(input, i);
	if (!new)
		return (-1);
	token_add_back(tokens, new);
	return (0);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		if (is_whitespace(input[i]))
			i++;
		else if (add_next_token(&tokens, input, &i) == -1)
			return (NULL);
	}
	return (tokens);
}
