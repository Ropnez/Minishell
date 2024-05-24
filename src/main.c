/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:01:59 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	if (argv && argc > 1)
	{
		ft_putstr_fd("Minishell can't take arguments\n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	env = init_minienv(envp);
	if (!env)
		return (EXIT_FAILURE);
	return (minishell(env, &exit_status));
}
