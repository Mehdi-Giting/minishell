/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 08:46:11 by marvin            #+#    #+#             */
/*   Updated: 2025/12/17 06:53:14 by marvin           ###   ########.fr       */
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

static int	copy_quoted_keep(char *input, int *j, char *buf, int *k)
{
	char	quote;

	quote = input[*j];
	buf[(*k)++] = input[(*j)++];   // copy opening quote
	while (input[*j] && input[*j] != quote)
		buf[(*k)++] = input[(*j)++];
	if (input[*j] != quote)
		return (-1);
	buf[(*k)++] = input[(*j)++];   // copy closing quote
	return (0);
}

t_token	*parse_word(char *input, int *i)
{
	char	*buf;
	int		j;
	int		k;
	t_token	*new;

	buf = malloc(ft_strlen(input + *i) + 1);
	if (!buf)
		return (NULL);
	j = *i;
	k = 0;
	while (input[j] && !is_whitespace(input[j]) && !is_operator_char(input[j]))
	{
		if (is_quote(input[j]))
		{
			if (copy_quoted_keep(input, &j, buf, &k) == -1)
				return (free(buf), NULL);
		}
		else
			buf[k++] = input[j++];
	}
	buf[k] = '\0';
	*i = j;
	new = token_new(TOK_WORD, buf);
	free(buf);
	return (new);
}
