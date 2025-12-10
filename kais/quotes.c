/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:00:00 by kfredj            #+#    #+#             */
/*   Updated: 2025/12/10 12:07:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	skip_word(char *line, int i)
{
	char	quote;

	quote = 0;
	while (line[i])
	{
		if (quote == 0 && (line[i] == '\'' || line[i] == '"'))
		{
			quote = line[i];
			i++;
		}
		else if (quote != 0 && line[i] == quote)
		{
			quote = 0;
			i++;
		}
		else if (quote == 0 && line[i] == ' ')
			break ;
		else
			i++;
	}
	return (i);
}

static void	copy_without_quotes(char *token, char *result)
{
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote = 0;
	while (token[i])
	{
		if (quote == 0 && (token[i] == '\'' || token[i] == '"'))
			quote = token[i++];
		else if (quote != 0 && token[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			result[j++] = token[i++];
	}
	result[j] = '\0';
}

char	*clean_quotes(char *token)
{
	char	*result;
	char	*old;

	if (!token)
		return (NULL);
	result = malloc(ft_strlen(token) + 1);
	if (!result)
		return (NULL);
	old = token;
	copy_without_quotes(token, result);
	free(old);
	return (result);
}

static void	fill_tokens(char **tokens, char *line)
{
	int	i;
	int	start;
	int	idx;

	i = 0;
	idx = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i])
		{
			start = i;
			i = skip_word(line, i);
			tokens[idx] = ft_substr(line, start, i - start);
			tokens[idx] = clean_quotes(tokens[idx]);
			idx++;
		}
	}
	tokens[idx] = NULL;
}

char	**split_with_quotes(char *line)
{
	char	**tokens;
	int		count;

	count = count_tokens_quotes(line);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	fill_tokens(tokens, line);
	return (tokens);
}
