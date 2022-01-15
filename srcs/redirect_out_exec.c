/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:05:52 by nferre            #+#    #+#             */
/*   Updated: 2022/01/15 17:59:11 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_while(int *i, t_token **tab)
{	
	while (tab[*i] && (*i > 0)
		&& (*i != get_first_operand_index(tab, *i)))
		*i -= 1;
	if (*i == get_first_operand_index(tab, *i))
		*i += 1;
}

int	first_ifs(int *i, t_token **tab, int i_to_exec, int *command_to_exec)
{
	int	fd;

	*i = i_to_exec - 1;
	if (g_data.create_file == 1 && tab[i_to_exec + 2] != NULL)
	{
		fd = open(tab[i_to_exec + 1]->value, O_WRONLY
				| O_TRUNC | O_CREAT, S_IRWXU);
		close(fd);
		return (1);
	}
	do_while(i, tab);
	if (get_nb_operand(tab, TOKEN_PIPE) == 1)
		g_data.exec_redirect_out = 1;
	if (g_data.create_file == 0)
	{
		g_data.create_file = 1;
		*command_to_exec = *i;
		fd = open(tab[i_to_exec + 1]->value, O_WRONLY
				| O_TRUNC | O_CREAT, S_IRWXU);
		close(fd);
		if (tab[i_to_exec + 2] != NULL)
			return (1);
	}
	return (0);
}

int	get_stdout(int *tmp_stdout, t_token **tab)
{
	if (get_nb_operand(tab, TOKEN_PIPE) == 0
		&& get_nb_operand(tab, TOKEN_REDIRECT_OUT) == 1)
		*tmp_stdout = dup(STDOUT_FILENO);
	return (0);
}

void	redirect_out_exec(t_token **tab, int i_to_exec)
{
	int			fd;
	int			tmp_stdout;
	int			i;
	static int	command_to_exec;

	if (first_ifs(&i, tab, i_to_exec, &command_to_exec) == 1)
		return ;
	get_stdout(&tmp_stdout, tab);
	fd = open(tab[i_to_exec + 1]->value, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (g_data.exec_redirect_out == 1)
		print_in_fd();
	else if (check_exec_builtins(tab, command_to_exec) == 0)
		find_exec(g_data.env, tab, command_to_exec);
	if (count_operand(tab, 0) > 1 && is_last_operand(tab, i_to_exec))
		redirect_stdout_stdin_pipe();
	else if (get_nb_operand(tab, TOKEN_PIPE) == 0
		&& get_nb_operand(tab, TOKEN_REDIRECT_OUT) == 1)
	{
		dup2(tmp_stdout, STDOUT_FILENO);
		close(tmp_stdout);
	}
	g_data.exec_redirect_out = 0;
	command_to_exec = 0;
}
