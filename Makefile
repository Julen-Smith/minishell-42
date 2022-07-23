SHELL = /bin/sh
NAME = minishell
CC		=	gcc
RM		=	rm -rf
FLAGS	=	-g3 -Wall -Wextra -Werror -g -fsanitize=address
SRC		=	src/minishell.c									\
			src/environment/environment.c					\
			src/parser/parser.c								\
			src/errors/error.c								\
			src/errors/string_errors.c						\
			src/redirections/redir.c						\
			src/utils/utils.c								\
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
			src/execution/execute_reddir.c					\
			src/signals/signals.c							\
			src/pipes/pipes.c								\
			src/quotes/quotes.c								\
			src/parser/parser_utils.c

INCLUDE =	/include/minishell.h
LIB		=	include/libraries/Libft/libft.a

PWD = ~/.brew/opt/readline

READLINE =	-I $(PWD)/include\
			-lreadline\
			-L $(PWD)/lib\

#READLINE =	-lreadline -L /Users/$(USER)/.brew/opt/readline/lib\
			-I /Users/$(USER)/.brew/opt/readline/include\ 

.c.o: $(SRC)
	@ $(CC) $(FLAGS) -o $@ -c $^ 

$(NAME): all

all: $(SRC)
	@$(MAKE) -C include/libraries/Libft/
	@ $(CC) $(FLAGS) $(SRC) $(LIB) $(READLINE) -I $(INCLUDE) -o $(NAME)
	@ echo "compilation OK"

clean:
	@$(RM) include/libraries/Libft/*.o
	@$(RM) *.o
	@ echo "clean done"

fclean: clean
	@$(MAKE) fclean -C include/libraries/Libft/
	@$(RM) minishell.dSYM
	@$(RM) $(NAME)
	@ echo "fclean done"

re: clean all

.PHONY: all clean fclean re
