/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:46:28 by aneitenb          #+#    #+#             */
/*   Updated: 2024/06/13 13:38:25 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	free_exec(t_exec *exe)
{
	if (exe->cmd_argv)
		free_2d_array(exe->cmd_argv);
	if (exe->redir.pipe_out == YES)
		free(exe->pipe_fd);
	if (exe->path)
		free(exe->path);
	if (exe->redir.hd_in == YES)
		unlink (exe->redir.hd_file);
	free (exe);
}

void	free_arg(t_shell *arg, int del_hist)
{
	size_t	i;

	i = 0;
	if (!arg || arg->count == 0)
		return ;
	while (i < arg->count)
	{
		if (arg[i].cmd.len == 0)
			vec_free(&arg[i].cmd);
		else if (arg[i].cmd.len != 0)
			vec_free_str(&arg[i].cmd);
		if (arg[i].rdrct.len == 0)
			vec_free(&arg[i].rdrct);
		else if (arg[i].rdrct.len != 0)
			vec_free_str(&arg[i].rdrct);
		if (arg->exe && arg->exe[i])
			free_exec(arg->exe[i]);
		i++;
	}
	free(arg->exe);
	if (del_hist == YES)
	{
		free_env(&arg->env);
		rl_clear_history();
	}
}

void	close_fds_exit(t_shell *arg, int ret)
{
	size_t	i;
	t_exec	*exe;

	i = 0;
	if (arg)
	{
		while (i < arg->count)
		{
			exe = arg->exe[i];
			if (exe)
				close_fds(exe);
			i++;
		}
		close_other_pipe_fds(arg, -5);
		free_arg(arg, YES);
	}
	exit (ret);
}

void	free_env(t_vec *env)
{
	size_t	i;
	char	**data;

	i = 0;
	data = (char **)env->memory;
	while (i < env->len)
	{
		free(data[i]);
		i++;
	}
	vec_free(env);
}

int	error_msg_free(int flag, char *str, char *specifier, t_vec *vec)
{
	if (flag == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(specifier, 2);
	}
	if (flag == 1)
	{
		ft_putstr_fd(str, 2);
	}
	if (vec)
		vec_free(vec);
	return (-1);
}
