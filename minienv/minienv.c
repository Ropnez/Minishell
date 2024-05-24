/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minienv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:02:27 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft/libft.h"

t_env	*free_env_list_error(t_env *list)
{
	ft_putstr_fd("Error: malloc failed\n", 2);
	free_minienv(&list);
	return (NULL);
}

t_env	*init_minienv(char **envp)
{
	t_env	*list;
	char	*home;
	int		i;

	list = NULL;
	i = 0;
	while (envp[i])
	{
		if (list_append(envp[i], &list) == -1)
			return (free_env_list_error(list));
		i++;
	}
	if (!minienv_node("OLDPWD", list))
		if (list_append("OLDPWD", &list) == -1)
			return (free_env_list_error(list));
	home = ft_strjoin("__HOME=", minienv_value("HOME", list));
	if (!home)
		return (free_env_list_error(list));
	if (list_append(home, &list) == -1)
		return (free_env_list_error(list));
	free(home);
	return (list);
}

int	list_append(char *key_pair, t_env **list)
{
	t_env	*new_node;
	t_env	*iter;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (-1);
	new_node->key_pair = ft_strdup(key_pair);
	if (!new_node->key_pair)
	{
		free(new_node);
		return (-1);
	}
	new_node->next = NULL;
	if (!*list)
	{
		*list = new_node;
		return (0);
	}
	iter = *list;
	while (iter->next)
		iter = iter->next;
	iter->next = new_node;
	return (0);
}
