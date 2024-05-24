/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:07:12 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"

static int	declare_env(t_env *minienv)
{
	t_env	*iter;

	iter = minienv;
	while (iter)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(name_only(iter->key_pair), STDOUT_FILENO);
		if (ft_strchr(iter->key_pair, '='))
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(value_only(iter->key_pair), STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		iter = iter->next;
	}
	return (0);
}

t_env	*minienv_node_equal(char *name, t_env *minienv)
{
	t_env	*iter;
	int		size;

	iter = minienv;
	size = ft_strlen(name);
	while (iter)
	{
		if (ft_strncmp(name, iter->key_pair, size) == 0)
			return (iter);
		iter = iter->next;
	}
	return (NULL);
}

void	minienv_update_equal(char *name, char *value, t_env *minienv)
{
	t_env	*iter;
	char	*new_keypair;
	int		size;
	int		i;

	iter = minienv_node_equal(name, minienv);
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

void	ft_export_check(char *key_pair, char *varname, t_env **minienv)
{
	if (minienv_node(varname, *minienv) && !ft_strchr(key_pair, '='))
		(void)0;
	else if (minienv_node(varname, *minienv) && ft_strchr(key_pair, '='))
		minienv_update(varname, value_only(key_pair), *minienv);
	else if (minienv_node_equal(varname, *minienv) && ft_strchr(key_pair, '='))
		minienv_update_equal(varname, value_only(key_pair), *minienv);
	else if (minienv_node_equal(varname, *minienv))
		(void)0;
	else
		list_append(key_pair, minienv);
}

int	builtin_export(char **args, t_env **minienv)
{
	char	*key_pair;
	char	*varname;
	int		exit_status;

	args++;
	exit_status = EXIT_SUCCESS;
	if (!*args)
		return (declare_env(*minienv));
	while (*args)
	{
		key_pair = *args;
		varname = name_only(key_pair);
		if (!is_valid_varname(varname) || str_equal(key_pair, "="))
		{
			print_varname_error_msg("export", key_pair);
			exit_status = EXIT_FAILURE;
		}
		else
			ft_export_check(key_pair, varname, minienv);
		free(varname);
		args++;
	}
	return (exit_status);
}
