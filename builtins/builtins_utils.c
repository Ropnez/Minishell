/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:09:24 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	if (!command)
		return (0);
	if (str_equal(command, "echo"))
		return (1);
	if (str_equal(command, "cd"))
		return (1);
	if (str_equal(command, "pwd"))
		return (1);
	if (str_equal(command, "export"))
		return (1);
	if (str_equal(command, "unset"))
		return (1);
	if (str_equal(command, "env"))
		return (1);
	if (str_equal(command, "exit"))
		return (1);
	return (0);
}
