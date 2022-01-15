/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_find_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 16:10:37 by nferre            #+#    #+#             */
/*   Updated: 2022/01/15 16:17:02 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_thing_in_fork_2(char **arg, char **path)
{
	int	wstatus;

	wait(&wstatus);
	g_data.exec = 0;
	g_data.term->c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, g_data.term);
	if (WIFEXITED(wstatus))
		g_data.last_exit_status = WEXITSTATUS(wstatus);
	free_all(arg, path);
}

void	end_find_exec(t_token **tab, int i_to_exec, char **path, char **arg)
{
	g_data.term->c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, g_data.term);
	g_data.exec = 0;
	g_data.last_exit_status = 127;
	printf("minishell: %s: command not found\n", tab[i_to_exec]->value);
	free_all(arg, path);
}

int	init_var(int *i, char *to_print)
{
	char	*cpy;

	*i = -1;
	g_data.exec = 1;
	g_data.term->c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, g_data.term);
	cpy = ft_getenv("PATH");
	if (!(cpy))
	{
		printf("minishell: %s: No such file or directory\n", to_print);
		free(cpy);
		return (1);
	}
	free(cpy);
	return (0);
}

int	last_if(t_token **tab, int i_to_exec, char **arg, char **path)
{
	if (access(tab[i_to_exec]->value, X_OK) != -1)
	{
		if (fork() != 0)
		{
			do_thing_in_fork_2(arg, path);
			return (1);
		}
		execve(tab[i_to_exec]->value, arg, g_data.env);
	}
	end_find_exec(tab, i_to_exec, path, arg);
	return (0);
}

void	free_tabb(char **tabb)
{
	free(tabb[0]);
	free(tabb[1]);
}
