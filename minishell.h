/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidaneitenbach <aidaneitenbach@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:22:10 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/19 21:09:44 by aidaneitenb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "builtins.h"
# include "utils.h"
# define PATH_MAX 4096

/****************************************
*	Standard output formatting: printf	*
*****************************************/
# include <stdio.h>

/************************************************************************
*	Command-line editing: readline, rl_clear_history, rl_on_new_line,	*
*	rl_replace_line, rl_redisplay, add_history 							*
*************************************************************************/
# include "readline/readline.h"
# include "readline/history.h"

/****************************************************************
*	Dynamic memory allocation and deallocation: malloc, free	*
*	Environment variable access: getenv							*
*****************************************************************/
# include <stdlib.h>

/************************************************************************
*	File I/O operations: write, access, open, read, close, 				*
*	Duplication of file descriptors and pipe creation: dup, dup2, pip	*
*	Terminal-related operations: isatty, ttyname, ttyslot, ioctl		*
*************************************************************************/
# include <unistd.h>

/************************************************************
*	Process management: fork, wait, waitpid, wait3, wait4	*
*************************************************************/
# include <sys/types.h>
# include <sys/wait.h>

/************************************************************
*	Signal handling and process termination: 				*
*	signal, sigaction, sigemptyset, sigaddset, kill, exit	*
*************************************************************/
# include <signal.h>

/********************************************************
*	File and directory operations, process execution:	*
*	getcwd, chdir, stat, lstat, fstat, unlink, execve	*
*********************************************************/
# include <sys/stat.h>
# include <fcntl.h>

/********************************************************
*	Directory manipulation: opendir, readdir, closedir	*
*********************************************************/
# include <dirent.h>

/****************************************
*	Error handling: strerror, perror	*
*****************************************/
# include <string.h>

/********************************************
*	Terminal control: tcsetattr, tcgetattr	*
*********************************************/
# include <termios.h>

/********************************************************
*	Terminal handling, cursor movement, and output: 	*
*	tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs	*
*********************************************************/
# include <curses.h>

# include <limits.h>

/****************************
*			MACROS			*
*****************************/
# define SYNTX "minishell: syntax error near unexpected token "
# define SUBSTR "minishell: substr error\n"
# define STRDUP "minishell: strdup error\n"
# define STRJOIN "minishell: strjoin error\n"
# define VECPUSH "minishell: vec_push error\n"
# define VECNEW "minishell: vec_new error\n"
# define UNMATCH "minishell: unexpected EOF while looking for matching "

/************************************
*			SHELL STRUCT			*
*************************************/
typedef struct s_shell
{
	t_vec	cmd;
	t_vec	rdrct;
	t_vec	env;
	char	*temp;
	size_t	count;
	size_t	pipe_count;
	size_t	gl_count;
	size_t	i;
	int		j;
	int		join_flag;
	int		end_flag;
	int		expand_flag;
	int		joinrd_flag;
	int		endrd_flag;
	int		expandrd_flag;
}	t_shell;

typedef struct s_vecjoin
{
	char	*base;
	char	*add;
	char	*fin;
	char	*remainder;
	size_t	base_len;
	size_t	add_len;
	size_t	fin_len;
    int		index;
}	t_vecjoin;

int		parse_input(t_shell *arg, char *buf);
int		error_msg(int flag, char *str, char *specifier);
int		error_msg_free(int flag, char *str, char *specifier, t_vec *larg);
int		error_triple_msg(int flag, char *first, char *sec, char *third);
/*		scan utils		*/
int		handle_start(char *buf, int i);
int		handle_q(char *buf, int i);
int		handle_qq(char *buf, int i);
int		handle_pipe(char *buf, int i);
int		handle_lessgreat(char *buf, int i);
int		skip_spaces(char *buf, int i);
/*		split utils		*/
int		split_input(char *buf, t_shell *arg, size_t pos, int i);
int		split_rest(char *buf, t_shell *arg, size_t pos);
int		store_q(char *buf, t_shell *arg, size_t pos, int i);
int		store_qq(char *buf, t_shell *arg, size_t pos, int i);
int		store_less(char *buf, t_shell *arg, size_t pos, int i);
int		store_great(char *buf, t_shell *arg, size_t pos, int i);
int		rdrct_file(char *buf, t_shell *arg, size_t pos, int i);
int		rdrct_q(char *buf, t_shell *arg, size_t pos, int i);
int		rdrct_qq(char *buf, t_shell *arg, size_t pos, int i);
int		store_double(char *buf, t_shell *arg, size_t pos, int i);
int		store_single(char *buf, t_shell *arg, size_t pos, int i);
int		push_expand_vector(char *buf, t_shell *arg, size_t pos, int i);
int		push_to_vector(char *buf, t_shell *arg, size_t pos, int i);
int		vec_join(t_shell *arg, size_t pos);
void	check_join(char *buf, t_shell *arg, size_t pos, int i);
void	check_joinrd(char *buf, t_shell *arg, size_t pos, int i);
int		store_specialrd_cmd(char *buf, t_shell *arg, size_t pos, int i);
int		push_redirect_vector(char *buf, t_shell *arg, size_t pos, int i);
int 	push_rdrct_expand_vector(char *buf, t_shell *arg, size_t pos, int i);
void	print_vectors(t_shell *arg);	//delete

#endif