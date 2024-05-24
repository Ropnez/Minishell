/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:00:41 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!is_whitespace(*str))
			return (0);
		str++;
	}
	return (1);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	has_pipe(char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str != '\'')
				str++;
		}
		if (*str == '"')
		{
			str++;
			while (*str != '"')
				str++;
		}
		if (*str == '|')
			return (1);
		str++;
	}
	return (0);
}

int	is_name_delimiter(char c)
{
	if (is_whitespace(c) || c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}
