/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:16:05 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/15 17:27:49 by hadufer          ###   ########.fr       */
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

void	*handler_function(int sig)
{
	if (sig == SIGINT)
	{
		if (g_data.exec == 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			printf("\nminishell$> ");
		}
		else
			printf("\n");
	}
	if (sig == SIGQUIT)
	{
		if (g_data.exec == 0)
		{
			rl_on_new_line();
			rl_redisplay();
		}
		else
			printf("Quit: 3\n");
	}
	return (NULL);
}

void	free_tab(t_token **tab)
{
	int	i;

	i = -1;
	if (tab == NULL)
		return ;
	while (tab[++i])
	{
		free(tab[i]->value);
		if (tab[i])
			free(tab[i]);
	}
	free(tab);
}
