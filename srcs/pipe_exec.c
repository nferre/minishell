/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:25:46 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/13 10:11:26 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <fcntl.h>

int	pipe_exec(t_token **tab, int i_to_exec)
{
	int	fd_pipe[2];
	int	i;
	int	pid_tmp[2];
	int tmp_STDOUT;
	int tmp_STDIN;

	i = i_to_exec - 1;
	if (((tab[i_to_exec]->e_type == TOKEN_PIPE && (tab[i_to_exec + 1] == NULL || tab[i_to_exec + 1]->value[0] == '\0')) || tab[0]->value[0] == '|'))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	// tab[i_to_exec] == operand
	tmp_STDOUT = dup(STDOUT_FILENO);
	tmp_STDIN = dup(STDIN_FILENO);
	pipe(fd_pipe);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[1]);
	while (tab[i] && (i > 0) && (i != get_first_operand_index(tab, i)))
		i--;
	if (i == get_first_operand_index(tab, i))
		i++;
	if (count_operand(tab, 0) == 1 || is_first_operand(tab, i_to_exec))
		if (check_exec_builtins(tab, i) == 0)
			find_exec(g_data.env, tab, i);
	dup2(tmp_STDOUT, STDOUT_FILENO);
	close(tmp_STDOUT);
	if (g_data.more_than_one_operand && is_last_operand(tab, i_to_exec))
	{
		redirect_stdout_pipe();
		if (check_exec_builtins(tab, i_to_exec) == 0)
			find_exec(g_data.env, tab, i_to_exec + 1);
		redirect_stdin_pipe();
	}
	else
	{
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
		if (check_exec_builtins(tab, i_to_exec + 1) == 0)
			find_exec(g_data.env, tab, i_to_exec + 1);
		dup2(tmp_STDIN, STDIN_FILENO);
		close(tmp_STDIN);
	}
	return (0);
}
