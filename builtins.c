/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 09:55:45 by nferre            #+#    #+#             */
/*   Updated: 2021/11/16 13:26:47 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	echo(char *str)
{
	char	*echo;
	int		i;
	int		ver;

	i = -1;
	ver = 0;
	echo = "echo";
	while (++i != 4)
		if (str[i] != echo[i])
			return ;
	while (str[i] == ' ')
		i++;
	while (str)
	printf("%s\n", str + i);
}

void	pwd(char *str, char **env)
{
	int	i;
	char	*pwd;
	char	cwd[255];

	pwd = "pwd";
	i = -1;
	while (++i != 3)
		if (pwd[0] != str[0])
			return ;
	while (str[i])
		if (str[i++] != ' ')
			return ;
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
}

void	cd(char *str)
{
	int	i;
	char *cd;

	cd = "cd";
	i = -1;
	while (++i != 2)
		if (cd[0] != str[0])
			return ;
	chdir(str + i + 1);
}
