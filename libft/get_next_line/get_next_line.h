/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:07:29 by ellabiad          #+#    #+#             */
/*   Updated: 2025/11/02 02:32:44 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*fill_stash(char *buffer, char *stash, int fd);
char	*fill_line(char **stash);
size_t	ft_gnl_strlen(const char *str);
char	*ft_gnl_strchr(char *str, char c);
char	*ft_gnl_strdup(char *str);
char	*ft_gnl_substr(char const *s, unsigned int start, size_t len);
char	*ft_gnl_strjoin(char *s1, char *s2);

#endif