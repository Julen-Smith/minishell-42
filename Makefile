CC				= gcc
NAME			= minishell

LIBFT			= include/libraries/Libft/
INCLUDE			= /include/minishell.h
LIB				= include/libraries/Libft/libft.a
LIB_SRC			= include/libraries/Libft/*.c 
LIB_HEADER		= include/libraries/Libft/libft.h	
READLINE_PATH	= ~/.brew/opt/readline
READLINE		= -I$(READLINE_PATH)/include -lreadline -L $(READLINE_PATH)/lib 
FLAGS			= -g3 -Wall -Wextra -Werror -g 
FILE_NAME		= minishell environment parser error string_errors redir utils free_things dollars dollar_value unset export export_utils echo cd pwd env \
					exit check_builtins redir_utils execute binary_manage binary_manage_utils execute_reddir signals pipes quotes parser_utils

SRCS			= src/minishell.c								\
				src/environment/environment.c					\
				src/parser/parser.c								\
				src/errors/error.c								\
				src/errors/string_errors.c						\
				src/redirections/redir.c						\
				src/utils/utils.c								\
				src/utils/free_things.c							\
				src/dollars/dollars.c							\
				src/dollars/dollar_value.c						\
				src/builtins/unset.c							\
				src/builtins/export.c							\
				src/builtins/export_utils.c						\
				src/builtins/echo.c								\
				src/builtins/cd.c								\
				src/builtins/pwd.c								\
				src/builtins/env.c								\
				src/builtins/exit.c								\
				src/builtins/check_builtins/check_builtins.c	\
				src/redirections/redir_utils.c					\
				src/execution/execute.c							\
				src/execution/binary_manage.c					\
				src/execution/binary_manage_utils.c				\
				src/execution/execute_reddir.c					\
				src/signals/signals.c							\
				src/pipes/pipes.c								\
				src/quotes/quotes.c								\
				src/parser/parser_utils.c						\



OBJS	= $(SRCS:.c=.o)

all: $(NAME)

.SILENT:

$(NAME) : $(OBJS)
	make -C $(LIBFT)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIB) $(READLINE)

%.o: %.c
	@${CC} ${FLAGS} -c $< -o $@

clean:
	make fclean -C $(LIBFT)
	$(RM) ./*/*/*.o
	$(RM) $(RM_OBJ)
	echo "clean done"

fclean: clean
	$(MAKE) fclean -C include/libraries/Libft/
	$(RM) $(RM_OBJ)
	rm -rf .DS_Store
	rm -rf .vscode
	rm -rf minishell.dSYM

	echo "fclean done"

re: clean all

.PHONY: all clean fclean re

