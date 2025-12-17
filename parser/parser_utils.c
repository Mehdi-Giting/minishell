/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:39:49 by marvin            #+#    #+#             */
/*   Updated: 2025/12/17 06:31:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **arg_list_to_argv(t_arg *args)
{
	char	**argv;
	int		count;
	t_arg	*tmp;

	tmp = args;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	tmp = args;
	count = 0;
	while (tmp)
	{
		argv[count++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	argv[count] = NULL;
	return (argv);
}

void	arg_add_back(t_arg **args, char *value)
{
	t_arg	*new;
	t_arg	*tmp;

	new = malloc(sizeof(t_arg));
	if (!new)
		return ;
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return ;
	}
	new->next = NULL;
	if (!*args)
	{
		*args = new;
		return ;
	}
	tmp = *args;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_cmd *cmd_new(void)
{
    t_cmd *new;

    new = malloc(sizeof(t_cmd));
    if (!new)
        return (NULL);
    new->tokens = NULL;
    new->is_builtin = 0;
    new->redirections = NULL;
    new->next = NULL;
    return (new);
}
