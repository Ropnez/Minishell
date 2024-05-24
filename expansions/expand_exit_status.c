/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:06:11 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include <stdlib.h>

static char	*find_exit_status_position(char *input)
{
	while (input && *input)
	{
		if (*input == '\'')
		{
			input++;
			while (*input && *input != '\'')
				input++;
		}
		if (*input == '\"')
		{
			input++;
			while (*input && *input != '\"')
			{
				if (*input == '$' && input[1] == '?')
					return (input);
				input++;
			}
		}
		if (*input == '$' && input[1] == '?')
			return (input);
		input++;
	}
	return (NULL);
}

static int	update_input(char **input, char *exit_code, char *second_part)
{
	char	*first_part;
	char	*updated_input;

	first_part = ft_strjoin(*input, exit_code);
	if (!first_part)
		return (-1);
	updated_input = ft_strjoin(first_part, second_part);
	if (!updated_input)
	{
		free(first_part);
		return (-1);
	}
	free(first_part);
	free(*input);
	*input = updated_input;
	return (0);
}

int	expand_exit_status(char **input, int exit_status)
{
	char	*exit_pos;
	char	*exit_str;

	exit_pos = find_exit_status_position(*input);
	if (exit_pos)
	{
		*exit_pos = '\0';
		exit_str = ft_itoa(exit_status);
		if (!exit_str)
			return (-1);
		if (update_input(input, exit_str, (exit_pos + 2)) == -1)
		{
			free(exit_str);
			return (-1);
		}
		free(exit_str);
		expand_exit_status(input, exit_status);
	}
	return (0);
}
