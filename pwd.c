/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:31:31 by nferre            #+#    #+#             */
/*   Updated: 2021/11/17 15:04:16 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	pwd(char *str, char **env)
{
	int	i;
	char	*pwd;
	char	cwd[255];

	pwd = "pwd";
	i = -1;
	while (str[i] == ' ')
		i++;
	while (++i != 3)
		if (pwd[0] != str[0])
			return (0);
	while (str[i])
		if (str[i++] != ' ')
			return (0);
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	return (1);
}
