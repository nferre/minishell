/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:55:24 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/11 18:19:54 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command(char *str)
{
	//je sais pas a quoi ca sert lol
	char	*temp;
	int	i;
	int	j;

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
	//free arg et path rien de special
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
	//permet de creer un double array qui va etre passer a execve, ce qui va permettre de de connaitre et d'exectuer les options d'une commande (ex : ls -l, permet de passer le -l pour execve)
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
	while(tab[tab_i])
	{
		if (tab[tab_i]->e_type != 0 && tab[tab_i]->e_type != 7 && tab[tab_i]->e_type != 8)
			break ;
		arg[i] = ft_strdup(tab[tab_i]->value);
		i++;
		tab_i++;
	}
	arg[i] = NULL;
	return (arg);
}

void new_file(t_token **tab, char *temp, char **env, char **arg)
{
	//permet de creer le fichier apres redirection (ex : ls > hassanfdp, creer le fichier hassanfdp)
	int	check;
	int	ver;
	int	file;
	char	*last_name;
	t_token **new;
	int	i;

	i = 0;
	check = 0;
	ver = 0;
	new = get_new_tab(tab, &ver, &check);
	while (check != 1)
	{
		if (i == 0)
			last_name = ft_strdup(new[0]->value);
		else
		{
			file = open(last_name, O_WRONLY | O_TRUNC);
			close(file);
		}
		free(new);
		new = get_new_tab(tab, &ver, &check);
		file = open(new[0]->value, O_WRONLY | O_CREAT, S_IRWXU | O_TRUNC);
		close(1);
		dup2(file, 1);
		if (check != 1)
		{
			if (fork() != 0)
			{
				wait(NULL);
				free(last_name);
				last_name = ft_strdup(new[0]->value);
				i++;
				close(file);
				continue ;
			}
		}
		free(last_name);
		execve(temp, arg, env);
	}
}

void	find_exec(char **env, t_token **tab, int i_to_exec)
{
	//cherche la commade a exectuer, si la commande n'est pas trouver cherche avec la commande de base
	//exemple : input = /bin/ls
	//cherche d'abord dans le PATH (example /sbin/bin/ls, puis /usr/local/bin/bin/ls)
	//si non essaie d'exectuer l'input directement, dans ce cas : /bin/ls -> execute donc la commande
	//si rien n'est trouver, affiche erreur commande not found
	char	**path;
	char	**arg;
	char	*temp;
	char	*temp2;
	char	*cpy;
	int		wstatus;
	int	i;
	int	file;

	i = -1;
	g_data.exec = 1;
	g_data.term->c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, g_data.term);
	cpy = getenv("PATH");
	if (!(cpy))
	{
		printf("minishell: %s: No such file or directory\n", tab[i_to_exec]->value);
		free(cpy);
		return ;
	}
	arg = get_arg(tab, i_to_exec);
	cpy = tab[i_to_exec]->value;
	path = ft_split(getenv("PATH") , ':');
	while (path[++i])
	{
		temp2 = ft_strjoin(path[i], "/");
		temp = ft_strjoin(temp2 , cpy);
		if (access(temp, X_OK) != -1)
		{
			if (fork() != 0)
			{
				wait(&wstatus);
				g_data.exec = 0;
				g_data.term->c_lflag &= ~ECHOCTL;
				tcsetattr(0, TCSANOW, g_data.term);
				if (WIFEXITED(wstatus))
					g_data.last_exit_status = WEXITSTATUS(wstatus);
				free(temp);
				free(temp2);
				free_all(arg, path);
				return ;
			}
			execve(temp, arg, env);
		}
		free(temp);
		free(temp2);
	}
	if (access(tab[i_to_exec]->value, X_OK) != -1)
	{
		if(fork() != 0)
		{
			wait(&wstatus);
			g_data.exec = 0;
			g_data.term->c_lflag &= ~ECHOCTL;
			tcsetattr(0, TCSANOW, g_data.term);
			if (WIFEXITED(wstatus))
				g_data.last_exit_status = WEXITSTATUS(wstatus);	
			free_all(arg, path);
			return ;
		}
		execve(tab[i_to_exec]->value, arg, env);
	}
	g_data.term->c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, g_data.term);
	g_data.exec = 0;
	g_data.last_exit_status = 1;
	printf("minishell: %s: command not found\n", tab[i_to_exec]->value);
	free_all(arg, path);
}
