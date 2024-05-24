/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:01:36 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAILED 0
# define PATH_MAX	4096
# define LLONG_MAX 9223372036854775807

# define NO_REDIRECT -1

# include <stdio.h>
# include "errors.h"
# include "minienv.h"
# include "builtins.h"
# include "executes.h"

int			minishell(t_env	*minienv, int *exit_status);
char		*prompt_input(t_env *minienv);
int			has_input_error(char *input, int *exit_status, t_env *minienv);
int			has_unclosed_quotes(char *str);
int			is_invalid_syntax(char *input);
int			is_invalid_token(char c);
int			unexpected_token(char *input);
int			syntax_error(char *token);
char		*get_next_pipe(char *str);
int			handle_heredoc(char *input, int *exit_status, t_env *minienv);
int			handle_expansions(char **input, t_env *minienv, int exit_status);
int			expand_variables(char **input, t_env *minienv);
int			expand_exit_status(char **input, int exit_status);
char		**split_commands(char *input);
char		**split_input(char *command);
void		define_main_signals(void);
void		define_execute_signals(int child_pid);
void		define_heredoc_signals(int child_pid);
int			str_equal(const char *str1, const char *str2);
int			is_quote(char c);
int			is_empty(char *str);
int			is_name_delimiter(char c);
int			has_pipe(char *str);
void		free_array(char **arr);
int			arr_len(char **arr);
long long	ft_atoll(const char *str);
void		move_one_forward(char *str);
char		*get_token_position(char *str, char *token);
int			skip_quotes(char *str);
t_env		*free_env_list_error(t_env *list);
int			is_whitespace(char c);

#endif
