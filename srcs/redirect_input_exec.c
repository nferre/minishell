/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:46:47 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/15 16:37:00 by hadufer          ###   ########.fr       */
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

void	in_exec_util(t_token **tab, int *it)
{
	while (tab[it[0]] && (it[0] > 0)
		&& (it[0] != get_first_operand_index(tab, it[0])))
		it[0]--;
	if (it[0] == get_first_operand_index(tab, it[0]))
		it[0]++;
	while (tab[it[1]])
	{
		if (get_first_operand_index(tab, it[1] + 1) == -1)
		{
			if (!g_data.more_than_one_operand)
				it[1]--;
			break ;
		}
		else
			it[1] = get_first_operand_index(tab, it[1] + 1);
		if (tab[it[1]]->e_type != TOKEN_REDIRECT_IN)
		{
			if (get_previous_operand_index(tab, it[1] - 1) > -1)
				it[1] = get_previous_operand_index(tab, it[1] - 1);
			break ;
		}
	}
	if (tab[it[1] + 1])
		it[3] = open(tab[it[1] + 1]->value, O_RDONLY);
}

void	in_exec_util2(t_token **tab, int *it, int i_to_exec)
{
	it[5] = dup(STDIN_FILENO);
	dup2(it[3], STDIN_FILENO);
	if (g_data.more_than_one_operand && is_first_operand(tab, i_to_exec))
		redirect_stdout_pipe();
	if (is_first_operand(tab, i_to_exec))
		find_exec(g_data.env, tab, it[0]);
	dup2(it[5], STDIN_FILENO);
	if (g_data.more_than_one_operand && is_last_operand(tab, i_to_exec))
		redirect_stdin_pipe();
}

int	in_exec_util3(t_token **tab, int *it, int i_to_exec)
{
	while (tab[it[1]])
	{
		if (it[1] == i_to_exec)
			break ;
		if ((get_previous_operand_index(tab, it[1] - 1) > -1)
			&& (it[1] > i_to_exec))
				((int *)it)[1] = get_previous_operand_index(tab, it[1] - 1);
		else
			break ;
		((int *)it)[4] = open(tab[it[1] + 1]->value, O_RDONLY);
		if (it[4] < 0)
		{
			printf("minishell: %s: No such file or directory `<'\n",
				tab[it[1] + 1]->value);
			return (1);
		}
		close(it[4]);
	}
	return (0);
}

int	redirect_in_exec(t_token **tab, int i_to_exec)
{
	const int	it[6] = {i_to_exec - 1, i_to_exec + 1, 0, 0};

	if (it[0] == -1)
	{
		printf("minishell: syntax error near unexpected token `<'\n");
		return (1);
	}
	in_exec_util(tab, (int *)it);
	if (!tab[it[1] + 2])
		((int *)it)[2] = 1;
	if (it[3] < 0)
	{
		printf("minishell: %s: No such file or directory `<'\n",
			tab[it[1] + 1]->value);
		return (1);
	}
	if (in_exec_util3(tab, (int *)it, i_to_exec) == 1)
		return (1);
	in_exec_util2(tab, (int *)it, i_to_exec);
	if (it[2])
		return (1);
	return (0);
}
