/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trufle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:03:44 by mehdi             #+#    #+#             */
/*   Updated: 2025/12/06 00:43:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**my_env;

	(void)argc;
	(void)argv;	
	my_env = ft_tabdup(envp);

	// ft_printf("---- ENV AFTER EXPORT ----\n");
	// int i = 0;
	// while (my_env[i])
	// {
	// 	ft_printf("%s\n", my_env[i]);
	// 	i++;
	// }

	// ---- Single command ----
	t_cmd cmd;
	cmd.tokens = (char *[]){"cd", "mehdi", NULL};
	cmd.is_builtin = 1;
	cmd.redirections = NULL;
	cmd.next = NULL;
	execute_command(&cmd, &my_env);
	// ft_printf("---- ENV AFTER EXPORT ----\n");
	// i = 0;
	// while (my_env[i])
	// {
	// 	ft_printf("%s\n", my_env[i]);
	// 	i++;
	// }

	ft_free_tab(my_env);
	// ---- Pipeline: ls | wc -l ----
	// t_cmd cmd1;
	// t_cmd cmd2;
	// t_cmd cmd3;

	// cmd1.tokens = (char *[]){"ls", NULL};
	// cmd1.is_builtin = 0;
	// cmd1.redirections = NULL;
	// cmd1.next = &cmd2;

	// cmd2.tokens = (char *[]){"grep", ".c", NULL};
	// cmd2.is_builtin = 0;
	// cmd2.redirections = NULL;
	// cmd2.next = &cmd3;

	// cmd3.tokens = (char *[]){"wc", "-l", NULL};
	// cmd3.is_builtin = 0;
	// cmd3.redirections = NULL;
	// cmd3.next = NULL;
	// execute_command(&cmd1, my_env);

	return (0);
}
