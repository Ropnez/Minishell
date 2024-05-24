/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:06:34 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <readline/readline.h>

static void	save_original_fds(int original_fds[2])
{
	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
}

int	*init_children_pid(char **commands, int *original_fds)
{
	int		*children_pid;
	size_t	size;

	save_original_fds(original_fds);
	size = sizeof(int) * (arr_len(commands) + 1);
	children_pid = malloc(size);
	if (!children_pid)
	{
		ft_putstr_fd("minishell: malloc error\n", STDERR_FILENO);
		free_array(commands);
		return (NULL);
	}
	ft_bzero(children_pid, size);
	return (children_pid);
}

void	clean_after_execute(int *children_pid)
{
	close_extra_fds();
	free(children_pid);
}

void	quit_child(char **commands, t_env **minienv)
{
	rl_clear_history();
	free_minienv(minienv);
	free_array(commands);
	close_all_fds();
	exit(EXIT_FAILURE);
}
