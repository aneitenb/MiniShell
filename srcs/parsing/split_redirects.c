/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:09:17 by aneitenb          #+#    #+#             */
/*   Updated: 2024/05/13 12:08:44 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/****************************************************************
*	Stores < or << redirection and its following file.			*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	store_less(char *buf, t_shell *arg, size_t pos, int i)
{
	arg->j = i;
	i++;
	if (buf[i] == '<')
		i = store_double(buf, arg, pos, i);
	else
		i = store_single(buf, arg, pos, i);
	i = skip_spaces(buf, i);
	arg->j = i;
	if (buf[i] == '\'')
		i = rdrct_q(buf, arg, pos, i);
	else if (buf[i] == '\"')
		i = rdrct_qq(buf, arg, pos, i);
	else
		i = rdrct_file(buf, arg, pos, i);
	return (i);
}

/****************************************************************
*	Stores > or >> redirection and its following file.			*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	store_great(char *buf, t_shell *arg, size_t pos, int i)
{
	arg->j = i;
	i++;
	if (buf[i] == '>')
		i = store_double(buf, arg, pos, i);
	else
		i = store_single(buf, arg, pos, i);
	i = skip_spaces(buf, i);
	arg->j = i;
	if (buf[i] == '\'')
		i = rdrct_q(buf, arg, pos, i);
	else if (buf[i] == '\"')
		i = rdrct_qq(buf, arg, pos, i);
	else
		i = rdrct_file(buf, arg, pos, i);
	return (i);
}