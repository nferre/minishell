/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:13:09 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/12 14:45:09 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Put more_than_one_operand to 1 and init fd_operand_pipe fd_base_stdin fd_base_stdout
// and redirect stdin, stdout to fd_operand_pipe
// in the case where there's more than 1 operand
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