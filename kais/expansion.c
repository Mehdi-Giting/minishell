/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:20:10 by marvin            #+#    #+#             */
/*   Updated: 2025/12/10 19:21:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_valid_var_char(char c, int is_first)
{
	if (is_first)
		return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_');
}

static int	get_var_len(char *str)
{
	int	len;

	if (str[0] == '?')
		return (1);
	len = 0;
	while (str[len] && is_valid_var_char(str[len], len == 0))
		len++;
	return (len);
}

static char	*get_var_value(char *var_name, int len)
{
	char	*value;
	char	*var;

	var = ft_substr(var_name, 0, len);
	if (!var)
		return (NULL);
	if (ft_strcmp(var, "?") == 0)
	{
		free(var);
		return (ft_strdup("0"));
	}
	value = getenv(var);
	free(var);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	free(s2);
	return (result);
}

char	*expand_variables(char *str)
{
	char	*result;
	char	*value;
	int		i;
	int		len;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			len = get_var_len(&str[i + 1]);
			if (len > 0)
			{
				value = get_var_value(&str[i + 1], len);
				result = join_and_free(result, value);
				i += len + 1;
				continue ;
			}
		}
		value = ft_substr(&str[i], 0, 1);
		result = join_and_free(result, value);
		i++;
	}
	return (result);
}
