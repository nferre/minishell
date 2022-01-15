/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input_here_exec.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:24:02 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/15 16:42:00 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	redirect_in_exec_util(t_token **tab, char *stop_word, int *it, int *pip)
{
	char	*tmp;

	tmp = NULL;
	pipe(pip);
	it[0] = dup(STDIN_FILENO);
	it[1] = dup(STDOUT_FILENO);
	while (1)
	{
		tmp = readline(">");
		if (!ft_strncmp(tmp, stop_word, ft_strlen_null(stop_word)))
			break ;
		ft_putendl_fd(tmp, pip[1]);
	}
	close(pip[1]);
	dup2(pip[0], STDIN_FILENO);
	find_exec(g_data.env, tab, it[2]);
	dup2(it[0], STDIN_FILENO);
}

int	redirect_in_heredoc_exec(t_token **tab, int i_to_exec)
{
	int		fd_pipe[2];
	int		it[3];
	char	*stop_word;

	it[2] = 0;
	if (!tab[i_to_exec + 1])
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	stop_word = tab[i_to_exec + 1]->value;
	while (tab[it[2]] && (it[2] > 0)
		&& (it[2] != get_first_operand_index(tab, it[2])))
		it[2]--;
	if (it[2] == get_first_operand_index(tab, it[2]))
		it[2]++;
	redirect_in_exec_util(tab, stop_word, it, fd_pipe);
	return (0);
}
