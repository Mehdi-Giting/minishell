/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 08:46:11 by marvin            #+#    #+#             */
/*   Updated: 2025/12/16 20:23:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	skip_quote(char *s, int i)
{
	char	quote;

	quote = s[i];
	i++;
	while (s[i])
	{
		if (s[i] == quote)
			return (i + 1);
		i++;
	}
	return (-1);
}

int	copy_quoted(char *input, int *j, char *buf, int *k)
{
	char	quote;

	quote = input[*j];
	(*j)++;
	while (input[*j] && input[*j] != quote)
	{
		buf[*k] = input[*j];
		(*k)++;
		(*j)++;
	}
	if (!input[*j])
		return (-1);
	(*j)++;
	return (0);
}

t_token	*parse_word(char *input, int *i)
{
	char	*buf;
	int		j;
	int		k;

	buf = malloc(ft_strlen(input + *i) + 1);
	if (!buf)
		return (NULL);
	j = *i;
	k = 0;
	while (input[j] && !is_whitespace(input[j]) && !is_operator_char(input[j]))
	{
		if (is_quote(input[j]))
		{
			if (copy_quoted(input, &j, buf, &k) == -1)
				return (free(buf), NULL);
		}
		else
			buf[k++] = input[j++];
	}
	buf[k] = '\0';
	*i = j;
	return (token_new(TOK_WORD, buf));
}
