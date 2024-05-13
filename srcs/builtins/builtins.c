/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:31:40 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/13 12:27:05 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	create_test_vector(t_vec *args, char *buf)
{
	char	**temp;
	int		i;

	i = 0;
	if (buf[i] == '\0')
	{
		args->memory = NULL;
		return ;
	}
	temp = ft_split(buf, ' ');
	vec_new(args, 10, sizeof(char *));
	while (temp[i])
	{
		vec_push(args, &temp[i]);
		i++;
	}
}

int	launch_builtin(t_vec *env, char *buf)
{
	char	**arg_strs;
	t_vec	args; //del when parsing is ready

	create_test_vector(&args, buf); //del when parsing is ready
	if (!args.memory)
		return (1);
	arg_strs = (char **)args.memory;
	if (ft_strncmp(arg_strs[0], "env", ft_strlen(arg_strs[0]) + 1) == 0)
		ft_env(env, &args);
	else if (ft_strncmp(arg_strs[0], "pwd", ft_strlen(arg_strs[0]) + 1) == 0)
		ft_pwd(env);
	else if (ft_strncmp(arg_strs[0], "unset", ft_strlen(arg_strs[0]) + 1) == 0)
		ft_unset(env, &args);
	else if (ft_strncmp(arg_strs[0], "export", ft_strlen(arg_strs[0]) + 1) == 0)
		ft_export(env, &args);
	else if (ft_strncmp(arg_strs[0], "echo", ft_strlen(arg_strs[0]) + 1) == 0)
		ft_echo(&args);
	else if (ft_strncmp(arg_strs[0], "cd", ft_strlen(arg_strs[0]) + 1) == 0)
		ft_cd(env, &args);
	// else if (ft_strncmp(args, "exit", ft_strlen(args)) == 0)
	// 	ft_exit();
	free_2d_array(arg_strs);
	return (0);
}
