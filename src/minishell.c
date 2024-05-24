/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:01:56 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	minishell(t_env *minienv, int *exit_status)
{
	char	*input;
	char	**commands;

	while (1)
	{
		define_main_signals();
		input = prompt_input(minienv);
		if (has_input_error(input, exit_status, minienv))
			continue ;
		if (handle_expansions(&input, minienv, *exit_status) == -1)
			continue ;
		if (!has_pipe(input))
			*exit_status = execute_one_command(input, &minienv);
		else
		{
			commands = split_commands(input);
			free(input);
			if (!commands)
				continue ;
			*exit_status = execute_multiple_commands(commands, &minienv);
			free_array(commands);
		}
	}
	return (*exit_status);
}
