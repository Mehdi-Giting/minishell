/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:03:44 by mehdi             #+#    #+#             */
/*   Updated: 2025/11/06 00:26:23 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	child;
	pid_t	status;
	char	*path;
	char	**args;

	if (argc > 1)
	{
		child = fork();
		if (child == 0)
		{	
			args = ft_split(argv[1], ' ');
			path = find_in_path(args[0]);
			if (!path)
			{
				perror("path");
				exit(1);
			}
			execve(path, args, envp);
			ft_free_tab(args);
			free(path);
			perror("execve");
			exit(1);
		}
		waitpid(child, &status, 0);
		if (WIFEXITED(status))
			printf("Child exited with status %d\n", WEXITSTATUS(status));
	}
	return (0);
}
