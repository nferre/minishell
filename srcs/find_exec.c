/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:58:37 by nferre            #+#    #+#             */
/*   Updated: 2021/11/22 09:55:27 by nferre           ###   ########.fr       */
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
	while (str[j] != ' ')
		j++;
	str[j] = '\0';
	temp = ft_strdup(str + i);
	return (temp);
}

void	find_exec(char *str, char **env)
{
	char	**path;
	char	**arg;
	char	*temp;
	char	*cpy;
	int	i;

	i = -1;
	arg = ft_split(str, ' ');
	cpy = get_command(str);
	path = ft_split(getenv("PATH") , ':');
	while (path[++i])
	{
		temp = ft_strjoin(ft_strjoin(path[i], "/"), cpy);
		if (access(temp, X_OK) != -1)
		{
			if (fork() != 0)
			{
				wait(NULL);
				return ;
			}
			execve(temp, arg, env);
		}
		free(temp);
	}
	if (access(str, X_OK) != -1)
	{
		if(fork() != 0)
		{
			wait(NULL);
			return ;
		}
		execve(str, arg, env);
	}
}
