/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:06:23 by mehdi             #+#    #+#             */
/*   Updated: 2025/11/06 00:15:26 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <sys/wait.h>

//Find the path for the command, return NULL if cannoct execute or dont find.
//TO DO : Once fully implemented, change the return the correct error value !!
char	*find_in_path(const char *cmd);

#endif