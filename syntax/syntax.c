/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:01:24 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f');
}

int	starts_with_pipe(char *input)
{
	if (input[0] == '|')
		return (syntax_error("|"));
	return (FALSE);
}

int	redirect_without_label(char *input)
{
	char	*redirect_position;
	char	next_redirect;

	next_redirect = get_next_redirect(input);
	redirect_position = get_redirect_position(input, next_redirect);
	if (!redirect_position)
		return (FALSE);
	if (redirect_position[0] == '<' && redirect_position[1] == '<')
		redirect_position++;
	else if (redirect_position[0] == '>' && redirect_position[1] == '>')
		redirect_position++;
	redirect_position++;
	while (is_whitespace(*redirect_position))
		redirect_position++;
	if (*redirect_position == '\0')
		return (syntax_error("newline"));
	if (is_invalid_token(*redirect_position))
		return (unexpected_token(redirect_position));
	return (redirect_without_label(redirect_position));
}

int	has_empty_pipe(char *input)
{
	char	*next_pipe;

	next_pipe = get_next_pipe(input);
	if (!next_pipe)
		return (FALSE);
	next_pipe++;
	while (is_whitespace(*next_pipe))
		next_pipe++;
	if (*next_pipe == '|')
		return (syntax_error("|"));
	return (has_empty_pipe(next_pipe));
}

int	is_invalid_syntax(char *input)
{
	if (starts_with_pipe(input))
		return (TRUE);
	if (redirect_without_label(input))
		return (TRUE);
	if (has_empty_pipe(input))
		return (TRUE);
	return (FALSE);
}
