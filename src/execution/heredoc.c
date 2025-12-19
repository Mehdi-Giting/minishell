/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:00:00 by marvin            #+#    #+#             */
/*   Updated: 2025/12/19 23:54:06 by marvin           ###   ########.fr       */
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

static int	create_heredoc_file(void)
{
	char	*template;
	int		fd;

	template = ft_strdup("/tmp/.heredoc_XXXXXX");
	if (!template)
		return (-1);
	fd = mkstemp(template);
	if (fd == -1)
	{
		free(template);
		perror("mkstemp");
		return (-1);
	}
	unlink(template);
	free(template);
	return (fd);
}

static int	read_heredoc_lines(int fd, char *delim, t_redir *redir, char **env)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		if (!redir->quoted)
			expanded = expand_string(line, env);
		else
			expanded = ft_strdup(line);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
		free(line);
	}
	return (0);
}

int	handle_heredoc(t_redir *redir, char **env)
{
	int		fd_write;
	int		fd_read;
	char	*clean_delim;

	fd_write = create_heredoc_file();
	if (fd_write == -1)
		return (-1);
	clean_delim = remove_delimiter_quotes(redir->file);
	if (!clean_delim)
		return (close(fd_write), -1);
	read_heredoc_lines(fd_write, clean_delim, redir, env);
	free(clean_delim);
	fd_read = dup(fd_write);
	lseek(fd_read, 0, SEEK_SET);
	close(fd_write);
	return (fd_read);
}
