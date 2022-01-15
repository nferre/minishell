/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:25:46 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/15 16:21:22 by hadufer          ###   ########.fr       */
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

void	pipe_util1(t_token **tab, int i_to_exec, int *fd_pipe, int *it)
{
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
		dup2(it[2], STDIN_FILENO);
		close(it[2]);
	}
}

void	pipe_util2(t_token **tab, int i_to_exec, int *it)
{
	while (tab[it[0]] && (it[0] > 0)
		&& (it[0] != get_first_operand_index(tab, it[0])))
		it[0]--;
	if (it[0] == get_first_operand_index(tab, it[0]))
		it[0]++;
	if (count_operand(tab, 0) == 1 || is_first_operand(tab, i_to_exec))
		if (check_exec_builtins(tab, it[0]) == 0)
			find_exec(g_data.env, tab, it[0]);
}

int	pipe_exec(t_token **tab, int i_to_exec)
{
	int	fd_pipe[2];
	int	it[3];

	it[0] = i_to_exec - 1;
	if (((tab[i_to_exec]->e_type == TOKEN_PIPE && (tab[i_to_exec + 1] == NULL
					|| tab[i_to_exec + 1]->value[0] == '\0'))
			|| tab[0]->value[0] == '|'))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	it[1] = dup(STDOUT_FILENO);
	it[2] = dup(STDIN_FILENO);
	pipe(fd_pipe);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[1]);
	pipe_util2(tab, i_to_exec, it);
	dup2(it[1], STDOUT_FILENO);
	close(it[1]);
	pipe_util1(tab, i_to_exec, fd_pipe, it);
	return (0);
}
