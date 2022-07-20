/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:50:51 by jsmith            #+#    #+#             */
/*   Updated: 2022/07/20 17:37:40 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <signal.h>
# include <sys/time.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/uio.h>
# include <sys/types.h>
# include "libraries/Libft/libft.h"
# include "libraries/GNL/get_next_line.h"

int		g_exit_status;
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
	ERR_REDDIR,
	ERR_PIPE,
	ERR_EMPTY_PIPE
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
	char	**command;
	bool	redir_exist;
	int		redircnt;
	int		*redirpos;
	char	**redirorder;
	char	**fd_collection;
	char	*bin_path;
	char	**path;
	bool	is_absolute;
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
	int			*pi;
	int			unipipe;
	int			cmd_count;
	t_command	*commands;
}	t_command_table;

char	**ft_duplicate_environment(char **str);
bool	last_chr_not_pipe(char *str);
int		ft_count_pipes(char *pnt);
int		parser(char *str, t_command_table *table);
bool	generate_command_table(char *str, int cmd_count,
			t_command_table *table);
int		process_string_quotes(char *not_processed_cmd);
bool	ft_error_print(int errnumb);

/*  Redirections */
bool	contains_redir(t_command *command);
bool	manage_redir_symbols(t_command *command);
int		lexer(t_command_table *table, t_msh_var *msh);
bool	char_is_redir(char command_i);
void	ft_fill_positions_to_command(t_command *command, int *position_stack);
bool	count_check_redirs(t_command *command);
void	*execute_reddir(t_command *table, t_msh_var *msh);

/*   Expansions    */
bool	ft_check_dollars(t_command_table *table, int i, int x, t_msh_var *msh);
int		ft_single_dollar(t_command *command, int arr_n, int xref);
void	ft_dollar_expansion(t_command *command,
			t_msh_var *msh, int arr_n, int xref);
char	*ft_dollar_value(t_command *com, t_msh_var *msh, int a_n, int xref);
void	ft_valuebeg(t_dollars *dollars, t_command *cm, int an, int x);
bool	ft_check_char(t_command *com, int a_n, int i, char *refs);

/* builtins */
void	ft_echo(t_command *command);
void	ft_pwd(void);
void	ft_env(t_msh_var *msh, t_command *command);
int		ft_exit(t_command *command, int c_num, int count);
bool	ft_cd(t_command *command, t_msh_var *msh, int count);
void	ft_check_unset(t_command *command, t_msh_var *msh);
void	ft_export_check(t_command *command, t_msh_var *msh);
bool	ft_check_variable(char *variable);
bool	ft_already_in(char *variable, char **env);
int		ft_parent_builtin(t_command *command, t_msh_var *msh, int n, int co);
int		ft_checkparent(t_command *command);
bool	ft_child_builtin(t_command *command, t_msh_var *msh);

/* Execution */
bool	return_binary_path(const char *bin_path, char *binary_check);
char	*reach_bin_path(t_command *command, t_msh_var *msh);
void	*execute(t_command_table *table, t_msh_var *msh);

/* String utils */
bool	_contains(char **command, char *str);
bool	_str_contains(char *command, char *str);
bool	_str_exactly_contains(char *command, char *str);
void	string_to_lower(char *pnt);
void	ft_freedollar_struct(t_dollars *dollars);
bool	check_if_empty_command(char *str);

/* Binary manage */
char	*reach_bin_path(t_command *command, t_msh_var *msh);
char	**get_actual_path(t_msh_var *msh);
bool	return_binary_path(const char *bin_path, char *binary_check);
bool	gather_bin_path(t_command_table *table, t_msh_var *msh);

/* Signals */
int		ft_interactive(int inter);
void	ft_signals(void);
void	ft_signal_exit(void);

/* Pipes managing */
char	*added_pipe(char *str);
bool	pipe_before_command(char *str);
bool	clean_double_pipes(char *str);


/* Quotes trimming */
void	ft_trim_algorithm(t_command *command, int i);
void	ft_quotetrim(t_command *command, int i, int final, int j);

/* Free memory */
void	ft_free_commands(t_command_table *table);

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
# define E_TARG ": numeric argument required"
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

#endif