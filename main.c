/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfredj <kfredj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:52:26 by kfredj            #+#    #+#             */
/*   Updated: 2025/11/18 12:30:00 by kfredj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// static void	print_redirections(t_redir *redir)
// {
// 	int		i;
// 	char	*type_str;
// 	char	*symbol;

// 	i = 1;
// 	while (redir)
// 	{
// 		if (redir->type == R_IN)
// 		{
// 			type_str = "Input";
// 			symbol = "<";
// 		}
// 		else if (redir->type == R_OUT)
// 		{
// 			type_str = "Output";
// 			symbol = ">";
// 		}
// 		else if (redir->type == R_APPEND)
// 		{
// 			type_str = "Append";
// 			symbol = ">>";
// 		}
// 		else if (redir->type == R_HEREDOC)
// 		{
// 			type_str = "Heredoc";
// 			symbol = "<<";
// 		}
// 		else
// 		{
// 			type_str = "Unknown";
// 			symbol = "?";
// 		}
// 		printf("     │  %-8s %-3s  →  %s\n", type_str, symbol,
// 			redir->file ? redir->file : "(none)");
// 		redir = redir->next;
// 		i++;
// 	}
// }

// static void	print_command_info(t_cmd *cmd)
// {
// 	int	i;

// 	if (!cmd)
// 		return ;
// 	printf("\n╔════════════════════════════════════════════════════════════╗\n");
// 	printf("║                    📋 COMMAND PARSING                      ║\n");
// 	printf("╚════════════════════════════════════════════════════════════╝\n");
// 	if (cmd->tokens)
// 	{
// 		printf("\n  🔹 Tokens (après nettoyage):\n");
// 		i = 0;
// 		while (cmd->tokens[i])
// 		{
// 			printf("     │  [%d] '%s'\n", i, cmd->tokens[i]);
// 			i++;
// 		}
// 		printf("\n  🔹 Built-in: %s\n", cmd->is_builtin ? "✅ YES" : "❌ NO");
// 	}
// 	else
// 		printf("\n  ⚠️  No tokens found\n");
// 	if (cmd->redirections)
// 	{
// 		printf("\n  🔹 Redirections détectées:\n");
// 		print_redirections(cmd->redirections);
// 	}
// 	else
// 		printf("\n  🔹 Redirections: aucune\n");
// 	printf("\n────────────────────────────────────────────────────────────\n");
// }

static void	free_redirections(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = tmp;
	}
}

static void	free_command(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->tokens)
		free_tokens(cmd->tokens);
	if (cmd->redirections)
		free_redirections(cmd->redirections);
	free(cmd);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	(void)envp;
	// printf("╔════════════════════════════════════════════════════════════╗\n");
	// printf("║              🐚  MINISHELL - DEBUG MODE  🐚                ║\n");
	// printf("╚════════════════════════════════════════════════════════════╝\n");
	// printf("\n💡 Commandes de test suggérées:\n");
	// printf("   • cat file.txt | grep hello | wc -l >output.txt\n");
	// printf("   • ls -la /tmp <input.txt >>log.txt 2>&1\n");
	// printf("   • echo \"Hello World\" >file1.txt >file2.txt\n");
	// printf("   • grep pattern <input.txt | sort | uniq >>results.txt\n");
	// printf("   • cat <<EOF >output.txt\n");
	// printf("\n📝 Type 'exit' ou Ctrl+D pour quitter\n");
	// printf("────────────────────────────────────────────────────────────\n\n");
	while (1)
	{
		line = read_command("minishell> ");
		if (!line || line[0] == '\0')
		{
			free(line);
			continue ;
		}
		cmd = struct_filer(split_command(line));
		is_built_in(cmd);
		execute_command(cmd, envp);
		//print_command_info(cmd);
		free_command(cmd);
		free(line);
	}
	return (0);
}
