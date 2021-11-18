/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:01:37 by nferre            #+#    #+#             */
/*   Updated: 2021/11/17 20:01:19 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_n(char *str)
{
	int	i;

	if (str[0] != '-' && str[1] != 'n')
		return (0);
	i = 1;
	while (str[i] == 'n')
		++i;
	if (str[i] != ' ')
		return (0);
	return (-1);
}

int	echo(char *str)
{
	char	*echo;
	int		i;
	int		ver;

	i = -1;
	ver = 0;
	echo = "echo";
	while (++i != 4)
		if (str[i] != echo[i])
			return (0);
	while (str[i] == ' ')
		i++;
	if (check_n(str + i) == 0)
	{
		printf("%s\n", str + i);
		return (1);
	}
	while (str[i] == ' ')
		i++;
	while (str[i] == '-')
		i++;
	while (str[i] == 'n')
		i++;
	while (str[i] == ' ')
		i++;
	printf("%s", str + i);
	return (1);
}
