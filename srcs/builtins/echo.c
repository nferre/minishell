/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:01:37 by nferre            #+#    #+#             */
/*   Updated: 2021/12/02 12:34:16 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_n(char *str)
{
	int	i;

	if (str[0] != '-' || str[1] != 'n')
		return (0);
	i = 1;
	while (str[i] == 'n')
		++i;
	if (str[i] != '\0')
		return (0);
	return (-1);
}

char	*echo(t_token **tab, int *j)
{
	char	*echo;
	int		i;
	int		ver;
	char	*to_print;

	i = -1;
	ver = 0;
	echo = "echo";
	while (++i != 4)
		if (tab[0]->value[i] != echo[i])
			return (0);
	if (check_n(tab[1]->value) == 0)
	{
		to_print = ft_strjoin(ft_strdup(tab[1]->value), "\n");
		*j += 1;
		return (to_print);
	}
	if (tab[2])
		to_print = ft_strdup(tab[2]->value);
	else
		to_print[0] = '\0';
	*j += 1;
	return (to_print);
}
