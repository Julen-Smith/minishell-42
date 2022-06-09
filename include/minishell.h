/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:50:51 by jsmith            #+#    #+#             */
/*   Updated: 2022/06/09 11:45:55 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libraries/Libft/libft.h"
# include "libraries/GNL/get_next_line.h"

struct	s_command;

/* Salidas */
enum	e_outfds
{
	IN,
	OUT,
	ERR
};

/* OWN DEFINED ERRORS */
enum e_own_err
{
	BASE,
	SUCCESS,
	ERR_NOT_WANNA_HANDLE,
	ERR_SIGSMTHG,
	ERR_UNDEFINED,
	ERR_QUOTATION,
	ERR_UNKNOWN,
	ERR_INVALIDCHR,
	ERR_FINALPIPE,
	ERR_COMMAND_404,
	ERR_REDDIR
};

typedef struct s_process_manager
{
	pid_t	father_pid;
}	t_process_manager;

typedef struct s_msh_var
{
	char	**own_envp;
	char	*pwd;
	char	*oldpwd;
	char	*path;
	char	*shlvl;
	char	*shellname;
}	t_msh_var;

/*char *binary; //binary array for error checking
, ex: "ls " should not execute to s_command*/
typedef struct s_command
{
    //char *binary; //binary array for error checking, ex: "ls " should not execute
    char **command;
    bool redir_exist;
    int redircnt;
    int *redirpos;
    char **redirorder;
	char **fd_collection;
	char *bin_path;
	char **path;
}	t_command;

//struct only used for dollar expansion
typedef struct s_dollars
{
	char	*beg;
	char	*final;
	char	*value;
	char	*result;
}	t_dollars;

typedef struct s_command_table
{
	int			cmd_count;
	t_command	*commands;
}	t_command_table;

char	**ft_duplicate_environment(char **str);
bool	last_chr_not_pipe(char *str);
int		ft_count_pipes(char *pnt);
int		parser(char *str, t_command_table *table);
void	generate_command_table(char *str, int cmd_count,
			t_command_table *table);
int		process_string_marks(char *not_processed_cmd);
bool	ft_error_print(int errnumb);

/*  Redirections */
bool	contains_redir(t_command *command);
bool	manage_redir_symbols(t_command *command);
int		lexer(t_command_table *table, t_msh_var *msh);
bool	char_is_redir(char command_i);
void	ft_fill_positions_to_command(t_command *command, int *position_stack);
bool	count_check_redirs(t_command *command);

/*   Expansions    */
int		ft_single_dollar(t_command *command, int arr_n, int xref);
void	ft_dollar_expansion(t_command *command,
			t_msh_var *msh, int arr_n, int xref);
char	*ft_dollar_value(t_command *com, t_msh_var *msh, int a_n, int xref);

/* builtins */
void			ft_echo(t_command *command);
void			ft_pwd(void);
void			ft_env(t_msh_var *msh);
void			ft_exit(void);
void			ft_cd(t_command *command, t_msh_var *msh);
int				ft_parent_builtin(t_command *command, t_msh_var *msh); // commands are lacking exit status

/* Execution */
bool return_binary_path(const char *bin_path, char *binary_check);
char *reach_bin_path(t_command *command, t_msh_var *msh);
void *execute(t_command_table *table, t_msh_var * msh);


/* String utils */
bool	_contains(char **command, char *str);
bool	_str_contains(char *command, char *str);
bool	_str_exactly_contains(char *command, char *str);

/*
bool            ft_error_print(int errnumb);
void            duplicate_environ(char **env, t_msh_var *msh);

void            store_father_pid(t_process_manager *p_manager, t_msh_var *msh);
void            init_msh(t_msh_var *msh,
					char **env, t_process_manager *p_manager);
int             process_string_marks(char *not_processed_cmd);
void            generate_command_table(char *str,
					int cmd_count, t_command_table *table);
int             ft_count_pipes(char *pnt);
int             parser(char *str, t_command_table *table);
bool            _contains(char *simple_command, char *str);
void            ft_print_own_environ(t_msh_var *msh);
*/
/* 
			-------------LITERALS -------------
*/

/* Buff if needed */
# define S_MAX  4096

/* MIN_INT */
# define MIN  -2147483648

/* Readline */
# define MSH "Minishell $ "

/* ERRORS */
# define QERROR "ERROR QUOTATION\n"
//#define ERROR "SIN MAS ERROR\n"
# define BAERR "bash:"
# define CMDNT ": command not found\n"
# define ERROR -1

/* BUILT */
# define LS "LS"
# define CD "CD"
# define PWD "PWD"
# define ENV "ENV"
# define ECHO "ECHO"
# define UNSET "UNSET"
# define EXPORT "EXPORT"
# define EXIT "exit"

/* CONST PATHS */
# define BIN "/bin/"
# define SBIN "/usr/bin/"

/* MODES */
# define PRINT 0
# define STORE 1
# define REFRESH 2

/* CMDS ELEMENTS */
# define HDC "<<"
# define APD ">>"
# define REDIPT "<"
# define REDOPT ">"

/* INVALIDS */
# define SMCOLON ";"
# define LSTPIPE "|"

typedef struct s_signal
{
	pid_t	pid;
}	t_signal;

typedef struct s_shell
{
	/* LAUNCH CONTROL */
	bool			islaunched;
	/*ENVIRON*/
	char			**envp;
	/*CMDS*/
	char			*cmd;
	char			**cmdsplit;
	char			*pwd;
	char			*cdhwhere;
	/*COUNT*/
	int				cmd_cnt;
	int				pipe_cnt;
	struct s_signal	sig;
}	t_shell;

#endif