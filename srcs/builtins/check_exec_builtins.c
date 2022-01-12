/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:21:36 by nferre            #+#    #+#             */
/*   Updated: 2022/01/12 13:20:30 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exec_builtins(t_token **tab, int i_to_exec)
{
	e_return_type_builtins builtin_executed;

	builtin_executed = echo(tab, i_to_exec);
	builtin_executed += cd(tab, g_data.env, i_to_exec);
	builtin_executed += show_env(tab, g_data.env, i_to_exec);
	builtin_executed += pwd(tab, i_to_exec);	
	builtin_executed += unset(tab, g_data.env, i_to_exec);	
	builtin_executed += export_var(tab, g_data.env, i_to_exec);	
	return (builtin_executed);
}
