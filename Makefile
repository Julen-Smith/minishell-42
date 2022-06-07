SHELL = /bin/sh
NAME = minishell
CC		=	gcc
RM		=	rm -rf
FLAGS	=	-g3 -fsanitize=address #-Wall -Wextra -Werror -g
SRC		=	src/minishell.c					\
			src/environment/environment.c	\
			src/parser/parser.c				\
			src/errors/error.c				\
			src/errors/string_errors.c		\
			src/redirections/redir.c		\
			src/utils/utils.c				\
			src/dollars/dollars.c			\
			src/dollars/dollar_value.c		\
			src/builtins/echo.c				\
			src/builtins/pwd.c				\
			src/builtins/env.c				\
			src/builtins/exit.c				\
			src/redirections/redir_utils.c


INCLUDE =	include/minishell.h
LIB		=	include/libraries/Libft/libft.a

PWD = ~/.brew/opt/readline

READLINE =	-lreadline -L /Users/$(USER)/.brew/opt/readline/lib\
			-I /Users/$(USER)/.brew/opt/readline/include\ 

$(NAME): all

all: $(SRC)
	@$(MAKE) -C include/libraries/libft/
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
