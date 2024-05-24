/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:08:26 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include <readline/readline.h>

int	fits_in_long_long(char *str)
{
	long long	out;
	int			c;

	if (ft_strlen(str) > 20)
		return (0);
	if (ft_strncmp(str, "-9223372036854775808", 21) == 0)
		return (1);
	out = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		c = *str - '0';
		if (out > (LLONG_MAX - c) / 10)
			return (0);
		out = out * 10 + c;
		str++;
	}
	return (1);
}

static void	check_args_error(char **args)
{
	char	*exit_status;

	if (!args || !args[1])
	{
		if (args)
			free_array(args);
		close_all_fds();
		exit(EXIT_SUCCESS);
	}
	exit_status = args[1];
	if (!fits_in_long_long(exit_status))
	{
		free_array(args);
		exit_with_error("exit", "numeric argument required", OUT_OF_RANGE);
	}
}

static int	ft_list_len(char **args)
{
	int	i;

	if (args == NULL)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	builtin_exit(char **args, t_env **minienv)
{
	int	exit_status;

	if (ft_list_len(args) > 2)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd ("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	rl_clear_history();
	free_minienv(minienv);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	check_args_error(args);
	close_all_fds();
	exit_status = ft_atoll(args[1]);
	free_array(args);
	exit(exit_status);
}
