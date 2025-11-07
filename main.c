/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:03:44 by mehdi             #+#    #+#             */
/*   Updated: 2025/11/07 23:31:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	t_cmd cmd;
	t_redir in;

	in.type = R_IN;
	in.file = "input.txt";
	in.next = NULL;

	cmd.argv = (char *[]){"cat", NULL};
	cmd.is_builtin = 0;
	cmd.redirections = &in;
	cmd.next = NULL;

	// ft_printf("minishel$> ");
	execute_command(&cmd, envp);
	return (0);
}
