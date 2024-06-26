NAME	=	minishell
CFLAGS	=	-Wall -Wextra -Werror -g
LDLIBS	=	-lreadline -lft
LDFLAGS	+= 	-L./libft
OBJ_DIR	=	obj
OBJS	=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
SRCS	=	$(MAIN) $(MINIENV) $(BUILTINS) $(EXECUTES) $(REDIRECTS) $(UTILS) \
			$(EXPANDS) $(SYNTAX)
MAIN	=	main.c minishell.c prompt.c split_commands.c handle_heredoc.c\
			input_error.c
SYNTAX	=	syntax.c syntax_utils.c
MINIENV	=	minienv.c minienv_utils.c minienv_str_utils.c free_minienv.c
BUILTINS =	builtins_utils.c echo.c cd.c pwd.c export.c unset.c env.c exit.c
EXECUTES =	execute_one_command.c execute_multiple_commands.c wait.c \
			execute_external.c execute_builtin.c split_input.c get_path.c \
			one_command_utils.c multiple_commands_utils.c pipes.c
REDIRECTS =	redirect_utils.c redirect_input.c redirect_output.c \
			redirect_heredoc.c
UTILS	=	error.c quote_checker.c signals.c str_utils.c str_checkers.c \
			ft_atoll.c free_array.c arr_len.c file_descriptors.c \
			get_label_name.c skip_quotes.c
EXPANDS	=	handle_expansions.c expand_variables.c expand_exit_status.c \
			variables_utils.c
LIBFT_A	=	./libft/libft.a
HEADER	=	minishell.h builtins.h errors.h executes.h minienv.h
VPATH	=	builtins minienv utils executes src redirects includes expansions \
			syntax
INCLUDE	=	-I ./ -I ./includes

all: $(NAME)

start: $(NAME)
	./$(NAME)

clean:
	@make -C libft fclean
	@rm -rf obj



fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS)


re: fclean all

$(LIBFT_A):
	@make --directory=./libft full

$(NAME): $(LIBFT_A) $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)


$(OBJ_DIR):
	@mkdir -p $@

.PHONY: all clean fclean re start
