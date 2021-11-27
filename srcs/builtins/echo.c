/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:01:37 by nferre            #+#    #+#             */
/*   Updated: 2021/11/27 13:31:50 by nferre           ###   ########.fr       */
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

char	*echo(char *str, int *j)
{
	char	*echo;
	int		i;
	int		ver;
	char	*to_print;

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
		to_print = ft_strdup(str + i);
		printf("%s\n", to_print);
		*j += 1;
		return (to_print);
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
	to_print = ft_strdup(str + i);
	*j += 1;
	return (to_print);
}
