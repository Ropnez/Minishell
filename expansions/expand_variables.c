/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:06:07 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include <stdlib.h>

static char	*find_var_position(char *input)
{
	while (*input)
	{
		if (*input == '\'')
		{
			input++;
			while (*input && *input != '\'')
				input++;
		}
		if (*input == '\"')
		{
			input++;
			while (*input && *input != '\"')
			{
				if (*input == '$' && is_varname(input[1]))
					return (input);
				input++;
			}
		}
		if (*input == '$' && is_varname(input[1]))
			return (input);
		input++;
	}
	return (NULL);
}

static int	update_input(char **input, char *value, char *second_part)
{
	char	*first_part;
	char	*updated_input;

	if (!*input[0] && !value)
		first_part = ft_strdup("");
	else if (!*input[0] && value)
		first_part = ft_strdup(value);
	else if (!value)
		first_part = ft_strdup(*input);
	else
		first_part = ft_strjoin(*input, value);
	if (!first_part)
		return (-1);
	updated_input = ft_strjoin(first_part, second_part);
	if (!updated_input)
	{
		free(first_part);
		return (-1);
	}
	free(first_part);
	free(*input);
	*input = updated_input;
	return (0);
}

int	expand_variables(char **input, t_env *minienv)
{
	char	*var_position;
	char	*var_name;
	char	*value;
	int		name_size;

	var_position = find_var_position(*input);
	if (var_position)
	{
		name_size = 0;
		while (is_varname(var_position[name_size + 1]))
			name_size++;
		var_name = ft_substr(var_position, 1, name_size);
		if (!var_name)
			return (-1);
		*var_position = '\0';
		value = minienv_value(var_name, minienv);
		if (update_input(input, value, (var_position + 1 + name_size)) == -1)
		{
			free(var_name);
			return (-1);
		}
		free(var_name);
		expand_variables(input, minienv);
	}
	return (0);
}
