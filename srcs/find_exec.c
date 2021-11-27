/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:58:37 by nferre            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/25 11:49:32 by hadufer          ###   ########.fr       */
=======
/*   Updated: 2021/11/27 13:29:31 by nferre           ###   ########.fr       */
>>>>>>> 223775915585397fd14033d5ad9bccad0a8612b4
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

void	free_all(char **arg, char **path, char *cpy)
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
	free(cpy);
}

void	find_exec(char *str, char **env)
{
	char	**path;
	char	**arg;
	char	*temp;
	char	*temp2;
	char	*cpy;
	int	i;

	i = -1;
	arg = ft_split(str, ' ');
	cpy = get_command(str);
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
				free_all(arg, path, cpy);
				return ;
			}
			execve(temp, arg, env);
		}
		free(temp);
		free(temp2);
	}
	if (access(str, X_OK) != -1)
	{
		if(fork() != 0)
		{
			wait(NULL);
			free_all(arg, path, cpy);
			return ;
		}
		execve(str, arg, env);
	}
	printf("minishell: %s: command not found\n", str);
	free_all(arg, path, cpy);
}
