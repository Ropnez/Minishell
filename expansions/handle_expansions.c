/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:06:04 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include "libft/libft.h"
#include <stdlib.h>

int	handle_expansions(char **input, t_env *minienv, int exit_status)
{
	if (expand_exit_status(input, exit_status) == -1)
	{
		ft_putstr_fd("minishell: malloc error\n", STDERR_FILENO);
		free(*input);
		return (-1);
	}
	if (expand_variables(input, minienv) == -1)
	{
		ft_putstr_fd("minishell: malloc error\n", STDERR_FILENO);
		free(*input);
		return (-1);
	}
	return (0);
}
