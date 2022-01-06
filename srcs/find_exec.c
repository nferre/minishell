/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:55:24 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/06 11:46:39 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command(char *str)
{
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

char	**get_arg(t_token **tab)
{
	int		i;
	char	**arg;

	i = 0;
	while (tab[i])
	{
		if (tab[i]->e_type != 0)
			break ;
		i++;
	}
	arg = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while(tab[++i])
	{
		if (tab[i]->e_type != 0)
			break ;
		arg[i] = ft_strdup(tab[i]->value);
	}
	arg[i] = NULL;
	return (arg);
}

void new_file(t_token **tab, char *temp, char **env, char **arg)
{
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

void	find_exec(t_token **new, char **env, t_token **tab)
{
	char	**path;
	char	**arg;
	char	*temp;
	char	*temp2;
	char	*cpy;
	int	i;
	int	file;

	i = -1;
	arg = get_arg(new);
	cpy = new[0]->value;
	path = ft_split(getenv("PATH") , ':');
	while (path[++i])
	{
		temp2 = ft_strjoin(path[i], "/");
		temp = ft_strjoin(temp2 , cpy);
		if (access(temp, X_OK) != -1)
		{
			if (fork() != 0)
			{
				wait(NULL);
				free(temp);
				free(temp2);
				free_all(arg, path);
				return ;
			}
			if (check_redirect(tab) == 0)
				execve(temp, arg, env);
			else
				new_file(tab, temp, env, arg);
		}
		free(temp);
		free(temp2);
	}
	if (access(new[0]->value, X_OK) != -1)
	{
		if(fork() != 0)
		{
			wait(NULL);
			free_all(arg, path);
			return ;
		}
		execve(new[0]->value, arg, env);
	}
	printf("minishell: %s: command not found\n", new[0]->value);
	free_all(arg, path);
}
