/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:03:26 by nferre            #+#    #+#             */
/*   Updated: 2022/01/06 17:01:59 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	unset(t_token **tab, char **env, int *g)
{
	int		i;
	int		j;
	int		k;
	char	*unset;

	unset = "unset";
	i = -1;
	j = -1;
	k = 0;
	while (++i != 5)
		if (tab[0]->value[i] != unset[i])
			return (0);
	i++;
	while (tab[1]->value[k])
		k++;
	while (env[++j])
	{
		if (ft_strncmp(env[j], tab[1]->value, k) == 0)
		{
			*g += 1;
			free(env[j]);
			env[j] = malloc(sizeof(char) * 14);
			env[j] = "7ca7486dfc94b";
			return (1);
		}
	}
	return (*g);
}
