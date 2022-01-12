/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:03:26 by nferre            #+#    #+#             */
/*   Updated: 2022/01/12 14:46:48 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	unset(t_token **tab, char **env, int i_to_exec)
{
	int		i;
	int		j;
	int		k;
	char	*unset;

	unset = "unset";
	i = -1;
	j = -1;
	k = 0;
	while (++i != 6)
		if (tab[i_to_exec]->value[i] != unset[i])
			return (0);
	i++;
	while (tab[i_to_exec + 1]->value[k])
		k++;
	while (env[++j])
	{
		if (ft_strncmp(env[j], tab[i_to_exec + 1]->value, k) == 0)
		{
			env[j][0] = '\0';
			return (5);
		}
	}
	return (5);
}
