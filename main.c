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

// #include "include/minishell.h"

// static void	print_tokens(t_cmd *cmd)
// {
// 	int	i;

// 	printf("  Tokens: ");
// 	if (!cmd->tokens || !cmd->tokens[0])
// 	{
// 		printf("(vide)\n");
// 		return ;
// 	}
// 	i = 0;
// 	while (cmd->tokens[i])
// 	{
// 		printf("[%s]", cmd->tokens[i]);
// 		if (cmd->tokens[i + 1])
// 			printf(" ");
// 		i++;
// 	}
// 	printf("\n");
// }

// static void	print_redirections(t_cmd *cmd)
// {
// 	t_redir	*redir;
// 	char	*type;

// 	redir = cmd->redirections;
// 	if (!redir)
// 		return ;
// 	printf("  Redirections:\n");
// 	while (redir)
// 	{
// 		if (redir->type == R_IN)
// 			type = "<";
// 		else if (redir->type == R_OUT)
// 			type = ">";
// 		else if (redir->type == R_APPEND)
// 			type = ">>";
// 		else
// 			type = "<<";
// 		printf("    %s %s\n", type, redir->file ? redir->file : "(vide)");
// 		redir = redir->next;
// 	}
// }

// static void	print_command(t_cmd *cmd, int num)
// {
// 	printf("\n┌─ Commande #%d ", num);
// 	printf("────────────────────────────────\n");
// 	print_tokens(cmd);
// 	print_redirections(cmd);
// 	is_built_in(cmd);
// 	printf("  Builtin: %s\n", cmd->is_builtin ? "OUI" : "NON");
// 	printf("└────────────────────────────────────────────────\n");
// }

// static void	free_all(t_cmd *cmd_list, char **segments, char *line)
// {
// 	t_redir	*tmp_redir;
// 	t_redir	*redir;
// 	t_cmd	*tmp_cmd;

// 	while (cmd_list)
// 	{
// 		tmp_cmd = cmd_list->next;
// 		if (cmd_list->tokens)
// 			free_tokens(cmd_list->tokens);
// 		redir = cmd_list->redirections;
// 		while (redir)
// 		{
// 			tmp_redir = redir->next;
// 			if (redir->file)
// 				free(redir->file);
// 			free(redir);
// 			redir = tmp_redir;
// 		}
// 		free(cmd_list);
// 		cmd_list = tmp_cmd;
// 	}
// 	if (segments)
// 		free_tokens(segments);
// 	if (line)
// 		free(line);
// }

// static void	process_line(char *line)
// {
// 	char	**segments;
// 	t_cmd	*cmd_list;
// 	t_cmd	*current;
// 	int		cmd_num;

// 	segments = split_command(line);
// 	cmd_list = struct_filer(segments);
// 	current = cmd_list;
// 	cmd_num = 0;
// 	while (current)
// 	{
// 		print_command(current, cmd_num);
// 		if (current->next)
// 			printf("        |\n        | PIPE\n        ↓\n");
// 		current = current->next;
// 		cmd_num++;
// 	}
// 	free_all(cmd_list, segments, line);
// }

// int	main(void)
// {
// 	char	*line;

// 	printf("╔════════════════════════════════════════════════╗\n");
// 	printf("║       🧪 MINISHELL - PARSER TEST 🧪           ║\n");
// 	printf("╚════════════════════════════════════════════════╝\n");
// 	printf("\n💡 Tapez 'exit' ou Ctrl+D pour quitter\n");
// 	printf("📋 Voir test_commands.txt pour les tests\n");
// 	printf("════════════════════════════════════════════════\n");
// 	while (1)
// 	{
// 		line = read_command("\nminishell> ");
// 		if (!line)
// 			break ;
// 		if (line[0] == '\0')
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		if (ft_strcmp(line, "exit") == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		process_line(line);
// 	}
// 	printf("\n👋 Au revoir!\n");
// 	return (0);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	char	**my_env;
// 	char	*line;
// 	char	**segments;
// 	t_cmd	*cmd_list;

// 	my_env = ft_tabdup(envp);
// 	setup_signals();
// 	while (1)
// 	{
// 		line = read_command("minishell> ");
// 		if (!line || line[0] == '\0')
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		segments = split_command(line);
// 		cmd_list = struct_filer(segments);
// 		g_last_exit_code = execute_command(cmd_list, &my_env);
// 		free_all(cmd_list, segments, line);
// 	}
// 	ft_free_tab(my_env);
// 	return (g_last_exit_code);
// }
