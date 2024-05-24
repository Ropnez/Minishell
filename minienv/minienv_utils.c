/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minienv_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:02:30 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft/libft.h"

char	*minienv_value(char *name, t_env *minienv)
{
	t_env	*iter;

	iter = minienv_node(name, minienv);
	if (!iter)
		return (NULL);
	return (value_only(iter->key_pair));
}

t_env	*minienv_node(char *name, t_env *minienv)
{
	t_env	*iter;
	int		size;

	iter = minienv;
	size = ft_strlen(name);
	while (iter)
	{
		if (ft_strncmp(name, iter->key_pair, size) == 0)
		{
			if (iter->key_pair[size] == '=')
				return (iter);
		}
		iter = iter->next;
	}
	return (NULL);
}

void	minienv_update(char *name, char *value, t_env *minienv)
{
	t_env	*iter;
	char	*new_keypair;
	int		size;
	int		i;

	iter = minienv_node(name, minienv);
	if (!iter)
	{
		new_keypair = create_keypair(name, value);
		list_append(new_keypair, &minienv);
		free(new_keypair);
		return ;
	}
	free(iter->key_pair);
	size = ft_strlen(name) + ft_strlen(value) + 2;
	new_keypair = malloc(size * sizeof(char));
	i = 0;
	while (*name)
		new_keypair[i++] = *name++;
	new_keypair[i++] = '=';
	while (*value)
		new_keypair[i++] = *value++;
	new_keypair[i] = '\0';
	iter->key_pair = new_keypair;
}

size_t	minienv_size(t_env *minienv)
{
	size_t	size;
	t_env	*iter;

	size = 0;
	iter = minienv;
	while (iter)
	{
		size++;
		iter = iter->next;
	}
	return (size);
}

char	**minienv_to_envp(t_env *minienv)
{
	char	**envp;
	t_env	*iter;
	int		i;

	envp = malloc(sizeof(char *) * (minienv_size(minienv) + 1));
	iter = minienv;
	i = 0;
	while (iter)
	{
		envp[i] = ft_strdup(iter->key_pair);
		i++;
		iter = iter->next;
	}
	envp[i] = NULL;
	return (envp);
}
