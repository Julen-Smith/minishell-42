SHELL = /bin/sh
NAME = minishell
CC		=	gcc
RM		=	rm -rf
FLAGS	=	#-Wall -Wextra -Werror -g -g3 -fsanitize=address
SRC		=	src/minishell.c	\
			src/environment/environment.c \
			src/parser/parser.c \
			src/errors/error.c \
			src/errors/string_errors.c \


INCLUDE =	include/minishell.h
LIB		=	include/libraries/libft/libft.a

PWD = ~/.brew/opt/readline

READLINE =	-lreadline -L /Users/$(USER)/.brew/opt/readline/lib\
			-I /Users/$(USER)/.brew/opt/readline/include\ 

$(NAME): all

all: $(SRC)
	@$(MAKE) -C include/libraries/libft/
	@ $(CC) $(FLAGS) $(SRC) $(LIB) $(READLINE) -I $(INCLUDE) -o $(NAME)
	@ echo "compilation OK"

clean:
	@$(RM) libft/*.o
	@$(RM) *.o
	@ echo "clean done"

fclean: clean
	@$(MAKE) fclean -C libft/
	@$(RM) minishell.dSYM
	@$(RM) $(NAME)
	@ echo "fclean done"

re: clean all

.PHONY: all clean fclean re
