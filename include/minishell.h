/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:06:23 by mehdi             #+#    #+#             */
/*   Updated: 2025/11/07 01:22:47 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <sys/wait.h>

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
	t_redir	*redirection;
	t_cmd	*next;
}	t_cmd;

char	*find_in_path(const char *cmd);

#endif