/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:08:31 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include "libft/libft.h"

int	env(t_env *minienv)
{
	t_env	*iter;

	iter = minienv;
	while (iter)
	{
		if (ft_strchr(iter->key_pair, '='))
		{
			ft_putstr_fd(iter->key_pair, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		iter = iter->next;
	}
	return (0);
}
