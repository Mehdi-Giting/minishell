/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:03:44 by mehdi             #+#    #+#             */
/*   Updated: 2025/12/24 13:40:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	process_input(char *input, char ***my_env)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(input);
	if (!tokens)
		return ;
	if (check_syntax(tokens) != 0)
	{
		free_tokens_p(tokens);
		return ;
	}
	cmds = parse_tokens(tokens);
	free_tokens_p(tokens);
	expand_cmds(cmds, *my_env);
	detect_builtins(cmds);
	process_all_heredocs(cmds, *my_env);
	g_last_exit_code = execute_command(cmds, my_env);
	free_cmds(cmds);
}

static int	read_and_execute(char ***my_env)
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
		return (0);
	if (*input)
		add_history(input);
	process_input(input, my_env);
	free(input);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	**my_env;

	(void)ac;
	(void)av;
	my_env = ft_tabdup(envp);
	setup_signals();
	while (read_and_execute(&my_env))
		;
	ft_free_tab(my_env);
	return (g_last_exit_code);
}
