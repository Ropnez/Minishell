/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buryilma <buryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:00:38 by buryilma          #+#    #+#             */
/*   Updated: 2023/12/10 09:05:52 by buryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define INTERRUPT 128
# define CMD_NOT_FOUND 127
# define PERMISSION_DENIED 126
# define NOT_EXECUTABLE 126
# define OUT_OF_RANGE 255
# define BUILTIN_MISUSE 2
# define FORK_ERROR -1
# define CMD_NOT_FOUND_MSG	"command not found"
# define NOT_EXECUTABLE_MSG "is a directory"

void	print_error_msg(char *command, char *msg);
void	exit_with_error(char *command, char *msg, int error);
void	print_perror_msg(char *command, char *perror_msg);
void	exit_with_perror(char *command, char *perror_msg, int error);
void	print_varname_error_msg(char *command, char *varname);

#endif
