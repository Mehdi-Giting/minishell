/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:09:54 by marvin            #+#    #+#             */
/*   Updated: 2025/12/20 09:07:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*extract_var_name(char *s, int *i)
{
	int		start;
	char	*key;

	if (s[*i] == '{')
	{
		(*i)++;
		start = *i;
		while (s[*i] && s[*i] != '}')
			(*i)++;
		if (s[*i] != '}')
			return (NULL);
		key = ft_substr(s, start, *i - start);
		(*i)++;
		return (key);
	}
	else
	{
		start = *i;
		while (ft_isalnum(s[*i]) || s[*i] == '_')
			(*i)++;
		return (ft_substr(s, start, *i - start));
	}
}

char	*expand_var(char *s, int *i, char **env)
{
	char	*key;
	char	*value;

	(*i)++;
	if (s[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_last_exit_code));
	}
	if (!ft_isalpha(s[*i]) && s[*i] != '_' && s[*i] != '{')
		return (ft_strdup("$"));
	key = extract_var_name(s, i);
	if (!key)
		return (ft_strdup(""));
	value = ft_getenv(key, env);
	free(key);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

int	handle_quote(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !(*in_double))
	{
		*in_single = !(*in_single);
		return (1);
	}
	if (c == '"' && !(*in_single))
	{
		*in_double = !(*in_double);
		return (1);
	}
	return (0);
}

void	handle_dollar(char *s, int *i, char **res, char **env)
{
	char	*expanded;

	expanded = expand_var(s, i, env);
	*res = str_append(*res, expanded);
	free(expanded);
}

void	append_char(char c, char **res)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	*res = str_append(*res, tmp);
}
