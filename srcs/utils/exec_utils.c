/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:13:09 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/15 13:06:10 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stdout_stdin_pipe(void)
{
	g_data.more_than_one_operand = 1;
	g_data.fd_base_stdin = dup(STDIN_FILENO);
	g_data.fd_base_stdout = dup(STDOUT_FILENO);
	pipe(g_data.fd_operand_pipe);
	dup2(g_data.fd_operand_pipe[1], STDOUT_FILENO);
	close(g_data.fd_operand_pipe[1]);
	dup2(g_data.fd_operand_pipe[0], STDIN_FILENO);
	close(g_data.fd_operand_pipe[0]);
}

void	redirect_stdout_stdin_pipe(void)
{
	redirect_stdin_pipe();
	redirect_stdout_pipe();
}

void	redirect_stdin_pipe(void)
{
	dup2(g_data.fd_base_stdin, STDIN_FILENO);
	close(g_data.fd_base_stdin);
}

void	redirect_stdout_pipe(void)
{
	dup2(g_data.fd_base_stdout, STDOUT_FILENO);
	close(g_data.fd_base_stdout);
}
