/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:00:00 by marvin            #+#    #+#             */
/*   Updated: 2025/12/24 11:46:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*remove_delimiter_quotes(const char *delim)
{
	char	*result;
	int		i;
	int		j;

	if (!delim)
		return (NULL);
	result = malloc(ft_strlen(delim) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (delim[i])
	{
		if (delim[i] != '\'' && delim[i] != '"')
			result[j++] = delim[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

static void	write_heredoc_line(int fd, char *line, t_redir *redir, char **env)
{
	char	*expanded;

	if (!redir->quoted)
		expanded = expand_string(line, env);
	else
		expanded = ft_strdup(line);
	write(fd, expanded, ft_strlen(expanded));
	write(fd, "\n", 1);
	free(expanded);
}

static int	read_heredoc_lines(int fd, char *delim, t_redir *redir, char **env)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(fd, line, redir, env);
		free(line);
	}
	return (0);
}

int	handle_heredoc(t_redir *redir, char **env)
{
	int		pipe_fd[2];
	char	*clean_delim;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	clean_delim = remove_delimiter_quotes(redir->file);
	if (!clean_delim)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	read_heredoc_lines(pipe_fd[1], clean_delim, redir, env);
	free(clean_delim);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}