/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:06:24 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft/libft.h"

static void	replace_spaces(char *str, char delimeter);
static void	restore_spaces(char **exec_args);
static int	contains_quote_mark(char *str);
static void	remove_quotes(char *str);

char	**split_input(char *command)
{
	char	**exec_args;

	if (!contains_quote_mark(command))
		return (ft_split(command, ' '));
	replace_spaces(command, '"');
	replace_spaces(command, '\'');
	remove_quotes(command);
	exec_args = ft_split(command, ' ');
	if (!exec_args)
		return (NULL);
	restore_spaces(exec_args);
	return (exec_args);
}

static void	restore_spaces(char **exec_args)
{
	char	*str;

	while (*exec_args)
	{
		str = *exec_args;
		while (*str)
		{
			if (*str == -1)
				*str = ' ';
			str++;
		}
		exec_args++;
	}
	return ;
}

static void	remove_quotes(char *str)
{
	char	last_opened;

	last_opened = 0;
	while (*str && !last_opened)
	{
		if (*str == '\'' || *str == '"')
		{
			last_opened = *str;
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
		}
		else
			str++;
	}
	while (*str && last_opened)
	{
		if (*str && *str == last_opened)
		{
			last_opened = 0;
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
		}
		else
			str++;
	}
	if (*str)
		return (remove_quotes(str));
}

static void	replace_spaces(char *str, char delimeter)
{
	while (*str && *str != delimeter)
		str++;
	if (*str)
		str++;
	while (*str && *str != delimeter)
	{
		if (is_whitespace(*str))
			*str = -1;
		str++;
	}
	if (*str)
		str++;
	if (*str)
		replace_spaces(str, delimeter);
}

static int	contains_quote_mark(char *str)
{
	if (!str)
		return (0);
	while (str && *str)
	{
		if (is_quote(*str))
			return (1);
		str++;
	}
	return (0);
}
