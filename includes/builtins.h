/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:05:56 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minienv.h"

int	is_builtin(char *command);
int	cd(char **args, t_env *minienv);
int	echo(char **args);
int	pwd(void);
int	builtin_export(char **args, t_env **minienv);
int	env(t_env *envp);
int	unset(char **args, t_env **minienv);
int	builtin_exit(char **args, t_env **minienv);
int	is_varname(char c);
int	is_valid_varname(char *name);

#endif
