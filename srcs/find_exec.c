/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:55:24 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/15 16:17:01 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command(char *str)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (str[i] == ' ')
		i++;
	j = i;
	while (str[j] != ' ' && str[j] != '\0')
		j++;
	str[j] = '\0';
	temp = ft_strdup(str + i);
	return (temp);
}

void	free_all(char **arg, char **path)
{
	int	i;

	i = -1;
	while (arg[++i])
		free(arg[i]);
	free(arg);
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}

char	**get_arg(t_token **tab, int i_to_exec)
{
	int		i;
	int		tab_i;
	char	**arg;

	i = i_to_exec;
	while (tab[i])
	{
		if (tab[i]->e_type != 0 && tab[i]->e_type != 7 && tab[i]->e_type != 8)
			break ;
		i++;
	}
	arg = malloc(sizeof(char *) * ((i - i_to_exec) + 1));
	i = 0;
	tab_i = i + i_to_exec;
	while (tab[tab_i])
	{
		if (tab[tab_i]->e_type != 0
			&& tab[tab_i]->e_type != 7 && tab[tab_i]->e_type != 8)
			break ;
		arg[i] = ft_strdup(tab[tab_i]->value);
		i++;
		tab_i++;
	}
	arg[i] = NULL;
	return (arg);
}

void	do_thing_in_fork(char *temp, char *temp2, char **arg, char **path)
{
	int	wstatus;

	wait(&wstatus);
	g_data.exec = 0;
	g_data.term->c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, g_data.term);
	if (WIFEXITED(wstatus))
		g_data.last_exit_status = WEXITSTATUS(wstatus);
	if (temp)
		free(temp);
	if (temp2)
		free(temp2);
	free_all(arg, path);
}

void	find_exec(char **env, t_token **tab, int i_to_exec)
{
	char	**path;
	char	**arg;
	char	*tabb[3];
	int		i;

	if (init_var(&i, tab[i_to_exec]->value) == 1)
		return ;
	arg = get_arg(tab, i_to_exec);
	tabb[2] = tab[i_to_exec]->value;
	tabb[0] = ft_getenv("PATH");
	path = ft_split(tabb[0], ':');
	free(tabb[0]);
	while (path[++i])
	{
		tabb[1] = ft_strjoin(path[i], "/");
		tabb[0] = ft_strjoin(tabb[1], tabb[2]);
		if (access(tabb[0], X_OK) != -1)
		{
			if (fork() != 0)
				return (do_thing_in_fork(tabb[0], tabb[1], arg, path));
			execve(tabb[0], arg, env);
		}
		free_tabb(tabb);
	}
	last_if(tab, i_to_exec, arg, path);
}
