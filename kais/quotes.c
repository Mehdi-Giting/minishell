/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:00:00 by kfredj            #+#    #+#             */
/*   Updated: 2025/12/17 12:09:17 by marvin           ###   ########.fr       */
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
			quote = line[i];
		else if (quote != 0 && line[i] == quote)
			quote = 0;
		else if (quote == 0 && line[i] == ' ')
			break ;
		i++;
	}
	return (i);
}

/*
 * FONCTION SIMPLE : process_token
 * Traite un token en fonction de son contexte (quotes ou pas)
 */
static char	*process_token(char *token)
{
	char	*result;
	char	quote;
	int		i;
	int		j;

	result = malloc(ft_strlen(token) * 4 + 1024);
	if (!result)
		return (NULL);
	
	i = 0;
	j = 0;
	quote = 0;
	
	while (token[i])
	{
		// Gestion des quotes
		if (quote == 0 && (token[i] == '\'' || token[i] == '"'))
		{
			quote = token[i];
			i++; // Sauter la quote ouvrante
			continue;
		}
		else if (quote != 0 && token[i] == quote)
		{
			quote = 0;
			i++; // Sauter la quote fermante
			continue;
		}
		
		// Expansion des variables (sauf dans single quotes)
		if (quote != '\'' && token[i] == '$' && token[i + 1])
		{
			char *var_value = NULL;
			int var_len = 0;
			
			i++; // Sauter le $
			
			// Cas spécial : $?
			if (token[i] == '?')
			{
				var_value = ft_strdup("0"); // TODO: vrai exit code
				var_len = 1;
			}
			// Variable normale
			else if ((token[i] >= 'A' && token[i] <= 'Z') ||
			         (token[i] >= 'a' && token[i] <= 'z') ||
			         token[i] == '_')
			{
				int start = i;
				while (token[i] && ((token[i] >= 'A' && token[i] <= 'Z') ||
				                    (token[i] >= 'a' && token[i] <= 'z') ||
				                    (token[i] >= '0' && token[i] <= '9') ||
				                    token[i] == '_'))
					i++;
				
				var_len = i - start;
				char *var_name = ft_substr(token, start, var_len);
				char *env_val = getenv(var_name);
				var_value = env_val ? ft_strdup(env_val) : ft_strdup("");
				free(var_name);
			}
			else
			{
				// $ seul ou suivi de caractère invalide
				result[j++] = '$';
				continue;
			}
			
			// Copier la valeur de la variable
			if (var_value)
			{
				int k = 0;
				while (var_value[k])
					result[j++] = var_value[k++];
				free(var_value);
			}
		}
		else
		{
			// Copie normale
			result[j++] = token[i++];
		}
	}
	
	result[j] = '\0';
	return (result);
}

char	*clean_quotes(char *token)
{
	char	*result;

	if (!token)
		return (NULL);
	
	result = process_token(token);
	free(token);
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
