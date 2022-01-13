/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:46:47 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/13 16:14:57 by hadufer          ###   ########.fr       */
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

int	redirect_in_exec(t_token **tab, int i_to_exec)
{
	int	i;
	int	j;
	int	fd;
	int fd2;
	int	tmp_stdin;

	i = i_to_exec - 1;
	j = i_to_exec + 1;
	if (i == -1)
	{
		printf("minishell: syntax error near unexpected token `<'\n");
		return (1);
	}
	tmp_stdin = dup(STDIN_FILENO);
	while (tab[i] && (i > 0) && (i != get_first_operand_index(tab, i)))
		i--;
	if (i == get_first_operand_index(tab, i))
		i++;
	while (tab[j])
	{
		if (get_first_operand_index(tab, j + 1) == -1)
		{
			if (!g_data.more_than_one_operand)
				j--;
			break ;
		}
		j = get_first_operand_index(tab, j + 1);
		if (tab[j]->e_type != TOKEN_REDIRECT_IN)
		{
			if (get_previous_operand_index(tab, j - 1) > -1)
				j = get_previous_operand_index(tab, j - 1);
			break ;
		}
	}
	if (tab[j + 1])
		fd = open(tab[j + 1]->value, O_RDONLY);
	if (fd < -1)
	{
		printf("minishell: %s: No such file or directory `<'\n", tab[j + 1]->value);
		return (1);
	}
	while (tab[j])
	{
		if (j == i_to_exec)
			break;
		if ((get_previous_operand_index(tab, j - 1) > -1) && (j > i_to_exec))
				j = get_previous_operand_index(tab, j - 1);
		else
			break ;
		fd2 = open(tab[j]->value, O_RDONLY);
		if (fd < -1)
		{
			printf("minishell: %s: No such file or directory `<'\n", tab[j + 1]->value);
			return (1);
		}
		close(fd2);
	}
	dup2(fd, STDIN_FILENO);
	if (g_data.more_than_one_operand && is_first_operand(tab, i_to_exec))
		redirect_stdout_pipe();
	if (is_first_operand(tab, i_to_exec))
		find_exec(g_data.env, tab, i);
	dup2(tmp_stdin, STDIN_FILENO);
	if (g_data.more_than_one_operand && is_last_operand(tab, i_to_exec))
		redirect_stdin_pipe();
	return (0);
}