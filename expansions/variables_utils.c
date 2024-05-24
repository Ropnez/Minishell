/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:06:00 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

int	is_varname(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_valid_varname(char *name)
{
	if (!ft_isalpha(*name) && *name != '_')
		return (FALSE);
	while (*name)
	{
		if (!is_varname(*name))
			return (FALSE);
		name++;
	}
	return (TRUE);
}
