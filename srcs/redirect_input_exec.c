/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:46:47 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/12 21:39:22 by nferre           ###   ########.fr       */
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
	int	fd;
	int	tmp_stdin;

	i = i_to_exec - 1;
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
	fd = open(tab[i_to_exec + 1]->value, O_RDONLY);
	if (fd < 0)
	{
		printf("minishell: syntax error near unexpected token `<'\n");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	find_exec(g_data.env, tab, i);
	dup2(tmp_stdin, STDIN_FILENO);
	return (0);
}
