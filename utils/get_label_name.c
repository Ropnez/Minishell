/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_label_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:01:01 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include "libft/libft.h"

static int	get_name_end(char *name)
{
	int	name_end;

	name_end = 0;
	while (name[name_end] && !is_name_delimiter(name[name_end]))
	{
		if (name[name_end] == '\'')
		{
			move_one_forward(&name[name_end]);
			while (name[name_end] && name[name_end] != '\'')
				name_end++;
			move_one_forward(&name[name_end]);
		}
		else if (name[name_end] == '"')
		{
			move_one_forward(&name[name_end]);
			while (name[name_end] && name[name_end] != '"')
				name_end++;
			move_one_forward(&name[name_end]);
		}
		else if (name[name_end] && !is_name_delimiter(name[name_end]))
			name_end++;
	}
	return (name_end);
}

char	*get_label_name(char *redirect_str)
{
	int		name_start;
	int		name_end;
	char	*name;
	char	*remaining_cmd;

	name_start = 0;
	move_one_forward(redirect_str);
	if (redirect_str[name_start] == '>')
		move_one_forward(&redirect_str[name_start]);
	while (is_whitespace(redirect_str[name_start]))
		name_start++;
	name_end = get_name_end(&redirect_str[name_start]);
	name = ft_substr(&redirect_str[name_start], 0, name_end);
	if (!name)
	{
		ft_putstr_fd("minishell: malloc error\n", STDERR_FILENO);
		return (NULL);
	}
	remaining_cmd = &redirect_str[name_start + name_end];
	ft_memmove(redirect_str, remaining_cmd, ft_strlen(remaining_cmd) + 2);
	return (name);
}
