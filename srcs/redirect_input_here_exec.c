/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input_here_exec.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:24:02 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/15 12:44:56 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	redirect_in_heredoc_exec(t_token **tab, int i_to_exec)
{
	int tmp_stdin;
	int tmp_stdout;
	int	fd_pipe[2];
	int	i;
	char	*tmp;
	char	*stop_word;

	i = 0;
	tmp = NULL;
	if (!tab[i_to_exec + 1])
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	stop_word = tab[i_to_exec + 1]->value;
	while (tab[i] && (i > 0) && (i != get_first_operand_index(tab, i)))
		i--;
	if (i == get_first_operand_index(tab, i))
		i++;
	pipe(fd_pipe);
	tmp_stdin = dup(STDIN_FILENO);
	tmp_stdout = dup(STDOUT_FILENO);
	while (1)
	{
		tmp = readline(">");
		if (!ft_strncmp(tmp, stop_word, ft_strlen_null(stop_word)))
			break ;
		ft_putendl_fd(tmp, fd_pipe[1]);
	}
	close(fd_pipe[1]);
	dup2(fd_pipe[0], STDIN_FILENO);
	find_exec(g_data.env, tab, i);
	dup2(tmp_stdin, STDIN_FILENO);
	return (0);
}
