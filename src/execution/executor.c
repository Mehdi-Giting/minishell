/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:37:05 by marvin            #+#    #+#             */
/*   Updated: 2025/12/19 23:55:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_command(t_cmd *cmd, char ***my_env)
{
	int	status;

	if (cmd->next)
		status = execute_pipeline(cmd, *my_env);
	else if (cmd->is_builtin)
		status = execute_builtin_with_redirections(cmd, my_env);
	else
		status = execute_simple_command(cmd, *my_env);
	return (status);
}
