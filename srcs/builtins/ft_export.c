/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:22:49 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/04 15:21:06 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	check_export_syntax(char *arg);
static int	export_variable(t_vec *env, char *arg);
static int	export_env_var(char *env_var, char *arg, t_vec *env);

int	ft_export(t_vec *env, t_vec *args)
{
	size_t		i;
	size_t		j;
	char		**arg_strs;

	i = 0;
	j = 0;
	arg_strs = (char **)args->memory;
	if (args->len == 1)
	{
		print_exports(env);
		return (0);
	}
	i++;
	while (i < args->len)
	{
		if (export_variable(env, arg_strs[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

static int	export_variable(t_vec *env, char *arg)
{
	char	*env_var;

	env_var = NULL;
	if (ft_strchr(arg, '=') != NULL && ft_strncmp(arg, "=", 2) != 0)
	{
		env_var = extract_env_var(arg);
		if (env_var == NULL)
			return (-1);
		if (check_export_syntax(env_var) < 0)
		{
			ft_fprintf(STDERR_FILENO, \
			"la_shell: export: `%s': not a valid identifier\n", env_var);
			return (-1);
		}
		else if (export_env_var(env_var, arg, env) < 0)
		{
			ft_fprintf(STDERR_FILENO, "la_shell: export: failed to export\n");
			return (-1);
		}
		free(env_var);
	}
	if (ft_strncmp(arg, "=", 2) == 0)
		return (ft_putendl_fd("la_shell: export: `=': not a valid identifier", \
		STDERR_FILENO), -1);
	return (0);
}

static int	check_export_syntax(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

static int	export_env_var(char *env_var, char *arg, t_vec *env)
{
	int			index;
	char		*temp;

	index = 0;
	if (getenv(env_var) == 0 && find_index_of_env(env, env_var) < 0)
	{
		temp = ft_strdup(arg);
		if (vec_push(env, &temp) < 0)
			return (-1);
		return (0);
	}
	else
	{
		index = find_index_of_env(env, env_var);
		if (index < 0)
			return (-1);
		temp = ft_strdup(arg);
		if (vec_replace_str(env, temp, index) < -1)
			return (-1);
	}
	return (0);
}
