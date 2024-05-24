/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:06:30 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	save_original_fd_in(int original_fds[2])
{
	if (original_fds[IN] == NO_REDIRECT)
		original_fds[IN] = dup(STDIN_FILENO);
}

void	save_original_fd_out(int original_fds[2])
{
	if (original_fds[OUT] == NO_REDIRECT)
		original_fds[OUT] = dup(STDOUT_FILENO);
}

int	handle_input_redirect(char *input, int original_fds[2])
{
	save_original_fd_in(original_fds);
	if (redirect_input(input) == FAILED)
	{
		redirect_fd(original_fds[IN], STDIN_FILENO);
		return (FAILED);
	}
	return (SUCCESS);
}

int	handle_output_redirect(char *input, int original_fds[2])
{
	save_original_fd_out(original_fds);
	if (redirect_output(input) == FAILED)
	{
		redirect_fd(original_fds[OUT], STDOUT_FILENO);
		return (FAILED);
	}
	return (SUCCESS);
}
