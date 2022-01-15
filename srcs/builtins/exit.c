/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:55:15 by nferre            #+#    #+#             */
/*   Updated: 2022/01/15 13:03:14 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	exit_all(t_token **tab)
{
	char	*end;
	int		i;

	i = -1;
	end = "exit";
	while (i++ != 4)
		if (tab[0]->value[i] != end[i])
			return ;
	printf("exit\n");
	if (tab[1])
	{
		i = -1;
		while (tab[1]->value[++i])
		{
			if (ft_isdigit(tab[1]->value[i]) == 0)
			{
				printf("minishell: exit: %s: numeric argument required\n",
					tab[1]->value);
				exit(255);
			}
		}
		exit(ft_atoi(tab[1]->value));
	}
	exit(0);
}
