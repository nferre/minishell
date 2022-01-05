/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:26:54 by nferre            #+#    #+#             */
/*   Updated: 2022/01/05 11:43:48 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	cd(t_token **tab)
{
	//cd need to go to ~/ when the input is 'cd'
	int	i;
	char *cd;

	cd = "cd";
	i = -1;
	while (++i != 2)
		if (cd[i] != tab[0]->value[i])
			return (0);
	chdir(tab[1]->value);
	return (1);
}
