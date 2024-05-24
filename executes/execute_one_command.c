/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:06:39 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static int	handle_redirects(char *input, int original_fds[2])
{
	char	redirect;

	original_fds[IN] = NO_REDIRECT;
	original_fds[OUT] = NO_REDIRECT;
	redirect = get_next_redirect(input);
	while (redirect)
	{
		if (redirect == '<')
		{
			if (!handle_input_redirect(input, original_fds))
				return (FAILED);
		}
		if (redirect == '>')
		{
			if (!handle_output_redirect(input, original_fds))
				return (FAILED);
		}
		if (redirect < 0)
		{
			save_original_fd_in(original_fds);
			redirect_heredoc(input, redirect);
		}
		redirect = get_next_redirect(input);
	}
	return (SUCCESS);
}

static void	restore_original_fds(int original_fds[2])
{
	if (original_fds[IN] != NO_REDIRECT)
		redirect_fd(original_fds[IN], STDIN_FILENO);
	if (original_fds[OUT] != NO_REDIRECT)
		redirect_fd(original_fds[OUT], STDOUT_FILENO);
}

int	execute_forked_external(char **args, t_env *minienv)
{
	int		child_pid;
	char	*command;

	command = args[0];
	child_pid = fork();
	define_execute_signals(child_pid);
	if (child_pid == -1)
		print_perror_msg("fork", command);
	else if (child_pid == 0)
		execute_external(args, minienv);
	else
		return (wait_for_child(child_pid, TRUE));
	exit(EXIT_FAILURE);
}

int	execute_one_command(char *input, t_env **minienv)
{
	char	**commands;
	int		exit_status;
	int		original_fds[2];

	if (!handle_redirects(input, &original_fds[0]))
	{
		restore_original_fds(original_fds);
		free(input);
		return (EXIT_FAILURE);
	}
	commands = split_input(input);
	if (!commands)
	{
		restore_original_fds(original_fds);
		free(input);
		return (EXIT_FAILURE);
	}
	free(input);
	if (is_builtin(commands[0]))
		exit_status = execute_builtin(commands, minienv);
	else
		exit_status = execute_forked_external(commands, *minienv);
	free_array(commands);
	restore_original_fds(original_fds);
	return (exit_status);
}
