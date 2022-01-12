/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:08:50 by nferre            #+#    #+#             */
/*   Updated: 2022/01/12 14:46:28 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	show_env(t_token **tab, char **env, int i_to_exec)
{
	int	i;
	char	*check;

	check = "env";
	i = -1;
	while (++i != 4)
		if (tab[i_to_exec]->value[i] != check[i])
			return (0);
	i = -1;
	while (env[++i])
		if (env[i][0] != '\0')
			printf("%s\n", env[i]);
	return (3);
}
