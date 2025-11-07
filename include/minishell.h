/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:06:23 by mehdi             #+#    #+#             */
/*   Updated: 2025/11/07 23:22:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <sys/wait.h>

typedef struct s_redir	t_redir;
typedef struct s_cmd	t_cmd;

typedef enum e_redir_type {
    R_IN,      // <
    R_OUT,     // >
    R_APPEND,  // >>
    R_HEREDOC  // <<
}   t_redir_type;

typedef struct s_redir
{
	char			*file;
	t_redir			*next;
	t_redir_type	type;
}	t_redir;

typedef struct	s_cmd
{
	char	**argv;
	int		is_builtin;
	t_redir	*redirections;
	t_cmd	*next;
}	t_cmd;

char	*find_in_path(const char *cmd);
int		execute_command(t_cmd *cmd, char **envp);
void	apply_redirections(t_redir *redirections);

#endif