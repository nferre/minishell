/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 10:31:18 by nferre            #+#    #+#             */
/*   Updated: 2021/11/29 14:48:41 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int check_export(t_token **tab)
{
	int	i;
	char	*export;

	i = 0;
	export = "export";
	while (export[i])
	{
		if (tab[0]->value[i] != export[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_arg(t_token **tab)
{
	int	i;

	i = -1;
	while (tab[1]->value[++i])
	{
		if (tab[1]->value[i] == '=')
			return (0);
	}
	return (1);
}

int	verify(t_token **tab)
{
	if (check_export(tab) == 1)
		return (1);
	else if (check_arg(tab) == 1)
		return (1);
	return (0);
}
