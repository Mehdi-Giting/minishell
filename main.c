/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:03:44 by mehdi             #+#    #+#             */
/*   Updated: 2025/11/06 05:01:44 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	child;
	pid_t	status;
	char	*path;
	char	*tmp;
	char	*comand_line;
	char	**args;

	(void)argv;
	(void)argc;
	while (1)
	{
		ft_printf("minishel$ ");
		tmp = get_next_line(STDIN_FILENO);
		comand_line = ft_strtrim(tmp, "\n");
		free(tmp);
		if (ft_strncmp(comand_line, "exit", ft_strlen("exit")) == 0)
			break ;
		args = ft_split(comand_line, ' ');
		path = find_in_path(args[0]);
		if (!path)
		{
			printf("%s", args[0]);
			free(comand_line);
			ft_free_tab(args);
			free(path);
			perror("path");
		}
		else
		{
			child = fork();
			if (child == 0)
			{
				execve(path, args, envp);
				ft_free_tab(args);
				free(path);
				perror("execve");
				exit(1);
			}
		}
		waitpid(child, &status, 0);
		if (WIFEXITED(status))
			printf("Child exited with status %d\n", WEXITSTATUS(status));
	}
	return (0);
}
