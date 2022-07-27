CC				= gcc
NAME			= minishell
OBJS			= $(SRCS:.c=.o)
SRC				= $(addsuffix .c, $(SRCS))
LIBFT			= include/libraries/Libft/.
INCLUDE			= /include/minishell.h
LIB				= include/libraries/Libft/libft.a
LIB_SRC			= include/libraries/Libft/*.c 
LIB_HEADER		= include/libraries/Libft/libft.h	
READLINE_PATH	= ~/.brew/opt/readline
READLINE		= -I $(READLINE_PATH)/include -lreadline -L $(READLINE_PATH)/lib 
FLAGS			= -g3 -Wall -Wextra -Werror -g #-fsanitize=address 
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

RM_OBJ			= src/minishell.o								\
				src/environment/environment.o					\
				src/parser/parser.o								\
				src/errors/error.o								\
				src/errors/string_errors.o						\
				src/redirections/redir.o						\
				src/utils/utils.o								\
				src/utils/free_things.o							\
				src/dollars/dollars.o							\
				src/dollars/dollar_value.o						\
				src/builtins/unset.o							\
				src/builtins/export.o							\
				src/builtins/export_utils.o						\
				src/builtins/echo.o								\
				src/builtins/cd.o								\
				src/builtins/pwd.o								\
				src/builtins/env.o								\
				src/builtins/exit.o								\
				src/builtins/check_builtins/check_builtins.o	\
				src/redirections/redir_utils.o					\
				src/execution/execute.o							\
				src/execution/binary_manage.o					\
				src/execution/binary_manage_utils.o				\
				src/execution/execute_reddir.o					\
				src/signals/signals.o							\
				src/pipes/pipes.o								\
				src/quotes/quotes.o								\
				src/parser/parser_utils.o						\

all: $(NAME)

.SILENT:
$(LIB) : $(LIB_SRC) $(LIB_HEADER)
	 $(MAKE) -C $(LIBFT)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(READLINE) $^ $(LIB) -I$(INCLUDE) -o $(NAME)

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

