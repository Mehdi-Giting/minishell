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

// static void	print_separator(void)
// {
// 	printf("\n");
// 	printf("═══════════════════════════════════════════════════════\n");
// }

// static void	print_tokens(char **tokens, char *label)
// {
// 	int	i;

// 	printf("\n%s:\n", label);
// 	if (!tokens)
// 	{
// 		printf("  (null)\n");
// 		return ;
// 	}
// 	i = 0;
// 	while (tokens[i])
// 	{
// 		printf("  [%d] '%s'\n", i, tokens[i]);
// 		i++;
// 	}
// }

// static void	print_redirections(t_redir *redir)
// {
// 	int		count;
// 	char	*type;

// 	count = 0;
// 	printf("\nRedirections:\n");
// 	if (!redir)
// 	{
// 		printf("  (aucune)\n");
// 		return ;
// 	}
// 	while (redir)
// 	{
// 		if (redir->type == R_IN)
// 			type = "<";
// 		else if (redir->type == R_OUT)
// 			type = ">";
// 		else if (redir->type == R_APPEND)
// 			type = ">>";
// 		else if (redir->type == R_HEREDOC)
// 			type = "<<";
// 		else
// 			type = "?";
// 		printf("  [%d] %s %s\n", count, type,
// 			redir->file ? redir->file : "(no file)");
// 		redir = redir->next;
// 		count++;
// 	}
// }

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

// static void	print_all_commands(t_cmd *cmd_list)
// {
// 	t_cmd	*current;
// 	int		cmd_num;

// 	current = cmd_list;
// 	cmd_num = 0;
// 	while (current)
// 	{
// 		printf("\n🔍 COMMANDE #%d:", cmd_num);
// 		print_tokens(current->tokens, "Tokens finaux (après nettoyage)");
// 		print_redirections(current->redirections);
// 		is_built_in(current);
// 		printf("\nBuiltin: %s\n", current->is_builtin ? "OUI ✅" : "NON ❌");
// 		if (current->next)
// 			printf("\n   ↓ PIPE vers commande suivante ↓\n");
// 		current = current->next;
// 		cmd_num++;
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	char	**my_env;
	(void)argc;
	(void)argv;
	char	*line;
	char	**segments;
	t_cmd	*cmd_list;

	my_env = ft_tabdup(envp);
	// printf("╔═══════════════════════════════════════════════════════╗\n");
	// printf("║          🧪 MINISHELL - TEST MODE 🧪                   ║\n");
	// printf("╚═══════════════════════════════════════════════════════╝\n");
	// printf("\n💡 Teste ces commandes:\n");
	// printf("   • cat file.txt\n");
	// printf("   • ls -la /tmp\n");
	// printf("   • echo hello >out.txt\n");
	// printf("   • cat <in.txt >>out.txt\n");
	// printf("   • grep test file.txt | wc -l\n");
	// printf("\n📌 Ctrl+D pour quitter\n");
	// print_separator();
	while (1)
	{
		setup_parent_signal();
		line = read_command("minishell> ");
		if (!line || line[0] == '\0')
		{
			free(line);
			continue ;
		}
		// printf("\n🔎 ÉTAPE 1: Découpe par pipes (|)");
		segments = split_command(line);
		// print_tokens(segments, "Segments");
		// printf("\n🔎 ÉTAPE 2: Traitement de TOUS les segments");
		cmd_list = struct_filer(segments);
		// printf("\n🔎 ÉTAPE 3: Résultat final");
		// print_all_commands(cmd_list);
		execute_command(cmd_list, &my_env);
		// print_separator();
		free_all(cmd_list, segments, line);
	}
	return (0);
}
