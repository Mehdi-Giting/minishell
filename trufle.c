/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trufle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:03:44 by mehdi             #+#    #+#             */
/*   Updated: 2025/12/16 20:16:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;
	char	**my_env;

	(void)ac;
	(void)av;
	my_env = ft_tabdup(envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		tokens = lexer(input);
		if (!tokens)
		{
			free(input);
			continue ;
		}
		if (check_syntax(tokens) != 0)
		{
			free_tokens_p(tokens);
			free(input);
			continue ;
		}
		cmds = parse_tokens(tokens);
		free_tokens_p(tokens);
		expand_cmds(cmds, my_env);
		detect_builtins(cmds);
		g_last_exit_code = execute_command(cmds, &my_env);
		free_cmds(cmds);
		free(input);
	}
	ft_free_tab(my_env);
	return (0);
}
