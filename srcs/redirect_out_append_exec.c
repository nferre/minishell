/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recirect_out_append_exec.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:24:26 by nferre            #+#    #+#             */
/*   Updated: 2022/01/13 18:57:10 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_out_append_exec(t_token **tab, int i_to_exec)
{
	int	fd;
	int	tmp_stdout;
	int	i;
	static int	command_to_exec;

	i = i_to_exec - 1;
	if (g_data.create_file == 1 && tab[i_to_exec + 2] != NULL)
	{
		fd = open(tab[i_to_exec + 1]->value, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
		close(fd);
		return ;
	}
	while (tab[i] && (i > 0) && (i != get_first_operand_index(tab, i)))
		i--;
	if (i == get_first_operand_index(tab, i))
		i++;
	if (g_data.create_file == 0)
	{
		g_data.create_file = 1;
		command_to_exec = i;
		fd = open(tab[i_to_exec + 1]->value, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU );
		close(fd);
		if (tab[i_to_exec + 2] != NULL)
			return ;
	}
	tmp_stdout = dup(STDOUT_FILENO);
	fd = open(tab[i_to_exec + 1]->value, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	if (check_exec_builtins(tab, command_to_exec) == 0)
		find_exec(g_data.env, tab, command_to_exec);
	dup2(tmp_stdout, STDOUT_FILENO);
	close(tmp_stdout);
	close(fd);
	if (count_operand(tab, 0) > 1 && is_last_operand(tab, i_to_exec))
			redirect_stdout_stdin_pipe();
	command_to_exec = 0;
}
