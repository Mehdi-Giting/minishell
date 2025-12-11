/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:00:00 by kfredj            #+#    #+#             */
/*   Updated: 2025/12/10 19:21:25 by marvin           ###   ########.fr       */
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

static char	*process_double_quotes(char *token, int *i, int *j, char *result)
{
	int		start;
	char	*expanded;
	int		k;

	(*i)++;
	start = *i;
	while (token[*i] && token[*i] != '"')
		(*i)++;
	expanded = ft_substr(token, start, *i - start);
	expanded = expand_variables(expanded);
	k = 0;
	while (expanded[k])
		result[(*j)++] = expanded[k++];
	free(expanded);
	if (token[*i] == '"')
		(*i)++;
	return (result);
}

static void	copy_with_expansion(char *token, char *result)
{
	int		i;
	int		j;
	// int		start;

	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '"')
			process_double_quotes(token, &i, &j, result);
		else if (token[i] == '\'')
		{
			i++;
			// start = i;
			while (token[i] && token[i] != '\'')
				result[j++] = token[i++];
			if (token[i] == '\'')
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
	result = malloc(ft_strlen(token) * 4 + 1);
	if (!result)
		return (NULL);
	old = token;
	copy_with_expansion(token, result);
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