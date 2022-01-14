/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out_append_exec.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:24:26 by nferre            #+#    #+#             */
/*   Updated: 2022/01/14 17:55:01 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_out_append_exec(t_token **tab, int i_to_exec)
{
	int	fd;
	int	tmp_stdout;
	int	i;
	static int	command_to_exec;
	static int	exec;

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
	if (get_nb_pipe_operand(tab) == 1)
		exec = 1;
	if (g_data.create_file == 0)
	{
		g_data.create_file = 1;
		command_to_exec = i;
		fd = open(tab[i_to_exec + 1]->value, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU );
		close(fd);
		if (tab[i_to_exec + 2] != NULL)
			return ;
	}
	if (i_to_exec == 1)
		tmp_stdout = dup(STDOUT_FILENO);
	fd = open(tab[i_to_exec + 1]->value, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (exec == 1)
		print_in_fd();
	else if (check_exec_builtins(tab, command_to_exec) == 0)
		find_exec(g_data.env, tab, command_to_exec);
	if (count_operand(tab, 0) > 1 && is_last_operand(tab, i_to_exec))
			redirect_stdout_stdin_pipe();
	else if (i_to_exec == 1)
	{
		dup2(tmp_stdout, STDOUT_FILENO);
		close(tmp_stdout);
	}
	exec = 0;
	command_to_exec = 0;
}
