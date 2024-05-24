/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:02:03 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	has_input_error(char *input, int *exit_status, t_env *minienv)
{
	int	result;

	result = FALSE;
	if (is_empty(input))
		result = TRUE;
	else if (has_unclosed_quotes(input))
		result = TRUE;
	else if (is_invalid_syntax(input))
	{
		*exit_status = 258;
		result = TRUE;
	}
	else if (handle_heredoc(input, exit_status, minienv) == FAILED)
		result = TRUE;
	if (result == TRUE)
		free(input);
	return (result);
}
