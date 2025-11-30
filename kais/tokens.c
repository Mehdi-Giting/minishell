/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:51:07 by kfredj            #+#    #+#             */
/*   Updated: 2025/11/30 16:47:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**split_command(char *line)
{
	char	**tokens;
	char	c;

	tokens = malloc(BUFSIZ * sizeof * tokens);
	c = '|';
	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	tokens = ft_split(line, c);
	return (tokens);
}

void	free_tokens(char **tokens)
{
	if (!tokens)
		return ;
	free(tokens);
}
t_cmd	*struct_filer(char **tokens)
{
	t_cmd	*cmd;
	int		i;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	/*is_built_in*/
	cmd->is_builtin = 0;
	cmd->redirections = NULL;
	cmd->next = NULL;
	i = 0;
	while (tokens[i])
	{
		tokens[i] = token_cleaner(tokens[i], cmd);
		i++;
	}
	cmd->tokens = tokens;
	return (cmd);
}
