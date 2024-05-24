/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:01:47 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft/libft.h"

static void	replace_pipes(char *str, char delimiter);
static void	restore_pipes(char **exec_args);

char	**split_commands(char *input)
{
	char	**commands;

	replace_pipes(input, '"');
	replace_pipes(input, '\'');
	commands = ft_split(input, '|');
	if (!commands)
		return (NULL);
	restore_pipes(commands);
	return (commands);
}

static void	replace_pipes(char *str, char delimiter)
{
	while (*str && *str != delimiter)
		str++;
	if (*str)
		str++;
	while (*str && *str != delimiter)
	{
		if (*str == '|')
			*str = -1;
		str++;
	}
	if (*str)
		str++;
	if (*str)
		replace_pipes(str, delimiter);
}

static void	restore_pipes(char **exec_args)
{
	char	*str;

	while (*exec_args)
	{
		str = *exec_args;
		while (*str)
		{
			if (*str == -1)
				*str = '|';
			str++;
		}
		exec_args++;
	}
	return ;
}
