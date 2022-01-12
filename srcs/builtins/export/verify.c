/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 10:31:18 by nferre            #+#    #+#             */
/*   Updated: 2022/01/12 15:39:56 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int check_export(t_token **tab, int i_to_exec)
{
	int	i;
	char	*export;

	i = -1;
	export = "export";
	while (++i != 7)
		if (tab[i_to_exec]->value[i] != export[i])
			return (1);
	return (0);
}

int	check_arg(t_token **tab, int i_to_exec)
{
	int	i;

	i = -1;
	while (tab[i_to_exec + 1]->value[++i])
		if (tab[i_to_exec + 1]->value[i] == '=')
			return (0);
	return (1);
}
