/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:13:09 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/11 18:51:33 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Put more_than_one_operand to 1 and init fd_operand_pipe fd_base_stdin fd_base_stdout
// and redirect stdin, stdout to fd_operand_pipe
// in the case where there's more than 1 operand
void	stdout_stdin_pipe()
{
	g_data.more_than_one_operand = 1;
	pipe(g_data.fd_operand_pipe);
	g_data.fd_base_stdin = dup(STDIN_FILENO);
	g_data.fd_base_stdout = dup(STDOUT_FILENO);
	close(g_data.fd_operand_pipe[1]);
	close(g_data.fd_operand_pipe[0]);
	dup2(g_data.fd_operand_pipe[1], STDIN_FILENO);
	dup2(g_data.fd_operand_pipe[0], STDOUT_FILENO);
}
