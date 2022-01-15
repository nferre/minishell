/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:36:50 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/15 17:10:06 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	init_global_data(char **env)
{
	g_data.env = env;
	g_data.last_exit_status = 0;
	g_data.exec = 0;
	g_data.check_rm = 0;
	g_data.more_than_one_operand = 0;
	g_data.create_file = 0;
	g_data.exec_redirect_out = 0;
	g_data.exec_redirect_append = 0;
}
