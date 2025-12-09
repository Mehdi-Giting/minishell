/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:39:18 by kfredj            #+#    #+#             */
/*   Updated: 2025/12/09 02:19:02 by marvin           ###   ########.fr       */
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

char	*expand_exit_code(char *token)
{
    // Si le token est exactement "$?"
    if (ft_strcmp(token, "$?") == 0)
    {
        return (ft_itoa(g_last_exit_code));
    }
    
    // Sinon, retourne une copie du token
    return (ft_strdup(token));
}