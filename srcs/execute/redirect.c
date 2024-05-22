/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:15:28 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/21 12:59:07 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	reset_fds(t_redir *redir)
{
	int	ret;

	ret = 0;
	if (!redir)
		return (0);
	if (redir->orig_fdin != -1)
	{
		if (dup2(redir->orig_fdin, STDIN_FILENO) == -1)
			ret = -1;
		close (redir->orig_fdin);
		redir->orig_fdin = -1;
	}
	if (redir->orig_fdout != -1)
	{
		if (dup2(redir->orig_fdout, STDIN_FILENO) == -1)
			ret = -1;
		close (redir->orig_fdout);
		redir->orig_fdout = -1;
	}
	return (ret);
}

int	set_fds(t_redir *redir, t_vec *rdrct, int *pipe_fd)
{
	 int	ret;

	 ret = 0;
	 if (!redir)
	 	return (-1);
	redir->orig_fdin = dup(STDIN_FILENO);
	if (redir->orig_fdin == -1)
		return (perror("dup failed"), -1); //
	redir->orig_fdout = dup(STDOUT_FILENO);
	if (redir->orig_fdout == -1)
		return (perror("dup failed"), -1); //
	if (redir->fd_in != -1)
		if (dup2(redir->fd_in, STDIN_FILENO) == -1)
			ret = error_triple_msg(3, "minishell :", "dup2 :", redir->infile); //
	if (redir->fd_out != -1)
		if (dup2(redir->fd_out, STDOUT_FILENO) == -1)
			ret = error_triple_msg(3, "minishell :", "dup2 :", redir->outfile); //
	return (ret);
}

int	check_files_and_fd(t_redir *redir)
{
	if (!redir || (!redir->infile || redir->outfile))
		return (-1);
	if ((redir->infile && redir->fd_in == -1)
		|| (redir->outfile && redir->fd_out == -1))
		return (-1);
	return (0);
}



int	set_pipe_fds(t_exec *exe, t_exec *pre)
{
	if (!exe)
		return (-1);
	if (pre && pre->redir.pipe_out)
		dup2(pre->pipe_fd[0], STDIN_FILENO);
	if (redir->pipe_out)
		dup2(exe->pipe_fd[1], STDOUT_FILENO);
	// might need to close all other fds in other t_exec to avoid fd leaks!
	return (1);
}

void close_pipe_fds(t_shell *arg, t_exec *exe, size_t pos)
{
	size_t	i;

	i = 0;
	while (i < &arg->count)
	{
		if (i != pos && &arg[i].exe->pipe_fd != 0)
		{
			close (arg[i]->exe->pipe_fd[0]);
			close (arg[i]->exe->pipe_fd[1]);
		}
		i++;
	}
}
