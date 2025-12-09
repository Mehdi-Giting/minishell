/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:51:07 by kfredj            #+#    #+#             */
/*   Updated: 2025/12/09 11:02:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**split_command(char *line)
{
	char	**tokens;
	char	c;

	c = '|';
	tokens = ft_split(line, c);
	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (tokens);
}

void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

char	**split_command2(char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	return (tokens);
}

static t_cmd	*create_single_cmd(char *segment)
{
	t_cmd	*cmd;
	char	**words;
	int		i;
	char	*tmp;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	cmd->is_builtin = 0;
	cmd->redirections = NULL;
	cmd->next = NULL;
	words = split_command2(segment);
	i = 0;
	while (words[i])
	{
		words[i] = token_cleaner(words[i], cmd);
		tmp = expand_exit_code(words[i]);
		if (ft_strcmp(tmp, "$?") != 0)
		{
			tmp = ft_strtrim(tmp, "\"\'");
			ft_printf("%s\n", tmp);
		}
        free(words[i]);
        words[i] = tmp;
		i++;
	}
	cmd->tokens = words;
	return (cmd);
}

t_cmd	*struct_filer(char **segments)
{
	t_cmd	*head;
	t_cmd	*current;
	int		i;

	if (!segments || !segments[0])
		return (NULL);
	head = create_single_cmd(segments[0]);
	is_built_in(head);
	current = head;
	i = 1;
	while (segments[i])
	{
		current->next = create_single_cmd(segments[i]);
		is_built_in(current->next);
		current = current->next;
		i++;
	}
	return (head);
}