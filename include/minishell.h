/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:06:23 by mehdi             #+#    #+#             */
/*   Updated: 2025/12/17 06:38:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <dirent.h>            // opendir, readdir, closedir
# include <fcntl.h>             // open, O_RDONLY, O_WRONLY
# include <readline/history.h>  // Fonctions d'historique
# include <readline/readline.h> // readline, rl_*, add_history
# include <signal.h>            // signal, sigaction, kill
# include <stdio.h>             // printf, perror
# include <stdlib.h>            // malloc, free, exit, getenv
# include <string.h>            // strerror
# include <sys/stat.h>          // stat, lstat, fstat
# include <sys/types.h>         // Types pour pid_t, size_t
# include <termios.h>           // tcsetattr, tcgetattr
# include <limits.h>            //PATH_MAX for pwd

extern int				g_last_exit_code; 
typedef struct s_redir	t_redir;
typedef struct s_cmd	t_cmd;

typedef enum e_redir_type {
    R_IN,      // <
    R_OUT,     // >
    R_APPEND,  // >>
    R_HEREDOC  // <<
}   t_redir_type;

typedef struct	s_cmd
{
	char			**tokens;
	int				is_builtin;
	t_redir			*redirections;
	t_cmd			*next;
}	t_cmd;

typedef struct s_redir
{
	char			*file;
	t_redir_type	type;
	t_redir			*next;
}	t_redir;

typedef enum e_token_type {
    TOK_WORD,
    TOK_PIPE,      // |
    TOK_REDIR_IN,  // <
    TOK_REDIR_OUT, // >
    TOK_APPEND,    // >>
    TOK_HEREDOC    // <<
} t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_arg
{
    char            *value;
    struct s_arg    *next;
} t_arg;


//---Mehdi
char	*find_in_path(const char *cmd);
int		execute_command(t_cmd *cmd, char ***my_env);
void	apply_redirections(t_redir *redirections);
void	child_command(t_cmd *cmd, char **my_env);
int		execute_pipeline(t_cmd *cmds, char **my_env);

int		exec_builtin(t_cmd *cmd, char ***my_env);
int		ft_pwd();
int		ft_echo(char **argv);
int		ft_cd(char **argv, char ***my_env);
int		ft_env(char **argv, char **my_env);
int		ft_export(char **argv, char ***my_env);
int		ft_unset(char **argv, char ***envp);
int		ft_exit(char **argv);
char	*ft_getenv(const char *key, char **my_env);
char	*ft_replace_env(const char *key, const char *value);
char	**ft_tabdup(char **my_env);
char	**ft_tabdup_add(char **my_env, const char *new_key);
void	ft_setenv(char *key, char *value, char ***my_env);
void	sort_env(char **env);
void	print_sorted_env(char **env);
int		export_one_arg(char *arg, char ***my_env);
int		is_valid_identifier(char *str);

void	setup_signals(void);
void    ignore_signals(void);
void    default_signals(void);
int		get_signal_exit_code(int status);

//---Kais
char	**split_command(char *line);
void	free_tokens(char **tokens);
char	*read_command(char *prompt);
int		if_redir(const char *line);
t_cmd	*struct_filer(char **tokens);
int		is_redirection(const char *token);
void	redir_finder(t_cmd *cmd);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*token_cleaner(char *token, t_cmd *cmd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
void	is_built_in(t_cmd *cmd);
int		count_tokens_quotes(char *line);
int		skip_word(char *line, int i);
char	*clean_quotes(char *token);
char	**split_with_quotes(char *line);
char	*expand_variables(char *str);

char	*expand_exit_code(char *token);

//--parser
int		is_whitespace(char c);
int		is_operator_char(char c);
int		is_quote(char c);
t_token	*token_new(t_token_type type, char *value);
void	token_add_back(t_token **head, t_token *new);
t_token	*lexer(char *input);
t_token	*parse_operator(char *input, int *i);
t_token	*parse_word(char *input, int *i);
int		skip_quote(char *s, int i);
int		check_syntax(t_token *token);
int		is_redir(t_token_type type);
t_cmd	*cmd_new(void);
void	arg_add_back(t_arg **head, char *value);
char	**arg_list_to_argv(t_arg *args);
void	add_redirection(t_cmd *cmd, t_redir_type type, char *file);
t_cmd	*parse_tokens(t_token *tokens);
char	*expand_var(char *s, int *i, char **env);
char 	*expand_string(char *s, char **env);
void 	expand_cmds(t_cmd *cmds, char **env);
int		handle_quote(char c, int *in_single, int *in_double);
void	handle_dollar(char *s, int *i, char **res, char **env);
void	append_char(char c, char **res);
char	*str_append(char *dst, char *src);
void	free_tokens_p(t_token *tokens);
void	free_argv(char **argv);
void	free_redirs(t_redir *redirs);
void	free_cmds(t_cmd *cmds);
int		is_builtin_name(char *cmd);
void	detect_builtins(t_cmd *cmds);
void	free_arg_list(t_arg *args);

#endif