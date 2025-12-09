/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfredj <kfredj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:52:26 by kfredj            #+#    #+#             */
/*   Updated: 2025/12/01 18:30:00 by kfredj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfredj <kfredj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:52:26 by kfredj            #+#    #+#             */
/*   Updated: 2025/12/01 18:30:00 by kfredj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	free_all(t_cmd *cmd_list, char **segments, char *line)
{
	t_redir	*tmp_redir;
	t_redir	*redir;
	t_cmd	*tmp_cmd;

	while (cmd_list)
	{
		tmp_cmd = cmd_list->next;
		if (cmd_list->tokens)
			free_tokens(cmd_list->tokens);
		redir = cmd_list->redirections;
		while (redir)
		{
			tmp_redir = redir->next;
			if (redir->file)
				free(redir->file);
			free(redir);
			redir = tmp_redir;
		}
		free(cmd_list);
		cmd_list = tmp_cmd;
	}
	if (segments)
		free_tokens(segments);
	if (line)
		free(line);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	**my_env;
	char	*line;
	char	**segments;
	t_cmd	*cmd_list;
	// int		exit_code;

	my_env = ft_tabdup(envp);
	setup_signals();
	while (1)
	{
		line = read_command("minishell> ");
		if (!line || line[0] == '\0')
		{
			free(line);
			continue ;
		}
		segments = split_command(line);
		cmd_list = struct_filer(segments);
		execute_command(cmd_list, &my_env);
		// exit_code = execute_command(cmd_list, &my_env);
		// printf("DEBUG: Last exit code = %d\n", exit_code);  // ← TEMPORAIRE pour debug
		free_all(cmd_list, segments, line);
	}
	ft_free_tab(my_env);
	return (g_last_exit_code);
}
