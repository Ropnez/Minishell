/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:07:02 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft/libft.h"

static void	remove_from_minienv(char *varname, t_env **minienv);
static void	minienv_del_next_node(t_env **node);

int	unset(char **args, t_env **minienv)
{
	char	*varname;
	int		exit_status;

	args++;
	exit_status = EXIT_SUCCESS;
	if (!*args)
		return (0);
	while (*args)
	{
		varname = *args;
		if (!is_valid_varname(varname))
		{
			print_varname_error_msg("unset", varname);
			exit_status = EXIT_FAILURE;
		}
		else
			remove_from_minienv(varname, minienv);
		args++;
	}
	return (exit_status);
}

static void	remove_from_minienv(char *varname, t_env **minienv)
{
	t_env	*iter;

	iter = *minienv;
	while (iter && iter->next)
	{
		if (ft_strncmp((iter->next)->key_pair, varname,
				ft_strlen(varname)) == 0)
			return (minienv_del_next_node(&iter));
		iter = iter->next;
	}
}

static void	minienv_del_next_node(t_env **node)
{
	t_env	*temp;

	temp = (*node)->next;
	(*node)->next = ((*node)->next)->next;
	free(temp->key_pair);
	free(temp);
}
