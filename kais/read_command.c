/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:39:18 by kfredj            #+#    #+#             */
/*   Updated: 2025/11/30 16:46:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*read_command(char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (!line)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (line[0] != '\0')
		add_history(line);
	return(line);
}
