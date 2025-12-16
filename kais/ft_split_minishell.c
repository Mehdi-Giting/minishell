/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:48:15 by marvin            #+#    #+#             */
/*   Updated: 2025/12/15 16:00:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_count_word(const char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			while (s[i] && s[i] != c)
				i++;
			word++;
		}
	}
	return (word);
}

static int	ft_count_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static char	**ft_split_pipe(const char *s)
{
	int		i;
	int		j;
	char	**dest;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!dest)
		return (NULL);
	while (i < ft_count_word(s, c))
	{
		while (s[j] == c)
			j++;
		if (s[j] != '\0' && s[j] != c)
		{
			dest[i] = ft_substr(s, j, ft_count_len(s + j, c));
			i++;
			j = j + ft_count_len(s + j, c);
		}
	}
	dest[i] = NULL;
	return (dest);
}
