/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:07:37 by marvin            #+#    #+#             */
/*   Updated: 2025/12/18 17:56:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*str_append(char *dst, char *src)
{
	char	*new;

	if (!dst)
		return (ft_strdup(src));
	new = ft_strjoin(dst, src);
	free(dst);
	return (new);
}

char	*expand_string(char *s, char **env)
{
	int		i;
	int		in_single;
	int		in_double;
	char	*res;

	i = 0;
	in_single = 0;
	in_double = 0;
	res = ft_strdup("");
	while (s[i])
	{
		if (handle_quote(s[i], &in_single, &in_double))
			i++;
		else if (s[i] == '$' && !in_single)
			handle_dollar(s, &i, &res, env);
		else
		{
			append_char(s[i], &res);
			i++;
		}
	}
	return (res);
}
