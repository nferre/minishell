/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:03:26 by nferre            #+#    #+#             */
/*   Updated: 2022/01/06 13:40:24 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	unset(char *str, char **env)
{
	int	i;
	int	j;
	int	k;
	char	*unset;

	unset = "unset";
	i = -1;
	j = -1;
	k = 0;
	while (++i != 5)
		if (str[i] != unset[i])
			return (0);
	i++;
	while (str[i])
	{
		i++;
		k++;
	}
	while (env[++j])
	{
		if (ft_strncmp(env[j], str + i - k, k) == 0)
		{
			free(env[j]);
			env[j] = NULL;
		}
	}
	return (1);
}
