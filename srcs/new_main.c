/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:49:49 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/15 17:25:43 by hadufer          ###   ########.fr       */
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

void	all_builtins_exec(t_token **tab, int i_to_exec)
{
	while (i_to_exec > -1)
	{
		if (tab[i_to_exec]->e_type == TOKEN_PIPE)
			pipe_exec(tab, i_to_exec);
		else if (tab[i_to_exec]->e_type == TOKEN_REDIRECT_OUT_APPEND)
			redirect_out_append_exec(tab, i_to_exec);
		else if (tab[i_to_exec]->e_type == TOKEN_REDIRECT_OUT)
			redirect_out_exec(tab, i_to_exec);
		else if (tab[i_to_exec]->e_type == TOKEN_REDIRECT_IN_HEREDOC)
			redirect_in_heredoc_exec(tab, i_to_exec);
		else if (tab[i_to_exec]->e_type == TOKEN_REDIRECT_IN)
			if (redirect_in_exec(tab, i_to_exec) != 0)
				break ;
		i_to_exec = get_first_operand_index(tab, i_to_exec + 1);
	}
}

void	all_builtins(t_token **tab, char **env)
{
	int	it[4];

	it[2] = 0;
	it[1] = 0;
	it[0] = 0;
	it[3] = get_first_operand_index(tab, 0);
	if (tab[0]->value[0] == '\0')
	{
		printf("minishell : : command not found\n");
		return ;
	}
	if (count_operand(tab, 0) > 1)
		stdout_stdin_pipe();
	all_builtins_exec(tab, it[3]);
	if (g_data.more_than_one_operand)
		redirect_stdout_stdin_pipe();
	g_data.more_than_one_operand = 0;
	g_data.create_file = 0;
	if (count_operand(tab, 0) == 0)
	{
		it[3] = 0;
		exit_all(tab);
		if (check_exec_builtins(tab, it[3]) == 0)
			find_exec(env, tab, 0);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*str;

	(void)argc;
	(void)argv;
	init_global_data(env);
	str = "\0";
	str = malloc(sizeof(char));
	prompt(str, env);
	return (0);
}
