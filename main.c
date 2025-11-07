/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:03:44 by mehdi             #+#    #+#             */
/*   Updated: 2025/11/07 07:25:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	t_cmd cmd;

	cmd.argv = (char *[]){"ls", "-la", NULL};
	cmd.is_builtin = 0;
	cmd.redirections = NULL;
	cmd.next = NULL;

	ft_printf("minishel$ ");
	execute_command(&cmd, envp);
	return (0);
}
