/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:02:19 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int	redirect_input(char *input)
{
	char	*input_redirect;
	char	*file_name;
	int		fd;

	input_redirect = get_redirect_position(input, '<');
	if (!input_redirect)
		return (1);
	file_name = get_label_name(input_redirect);
	if (!file_name)
		return (0);
	fd = open(file_name, O_RDONLY, FD_CLOEXEC);
	if (fd == -1)
	{
		print_perror_msg("open", file_name);
		free(file_name);
		return (0);
	}
	else
		redirect_fd(fd, STDIN_FILENO);
	free(file_name);
	return (1);
}
