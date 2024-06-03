/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:28:32 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/03 16:33:20 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		expand_variables(t_vec *env, t_vec *vec, int index);
char	*extract_env_var(char *arg);
int		check_if_exists(t_vec *env, t_expd *s);
int		expand_string(t_vec *env, t_expd *s, t_vec *vec, int index);
int		expand_to_env_var(t_vec *env, t_expd *s, t_vec *vec, int index);
int		expand_to_exit_status(t_expd *s, t_vec *vec);
int		expand_to_empty(t_expd *s, t_vec *vec, int index);
void	free_expd(t_expd *s);

#endif