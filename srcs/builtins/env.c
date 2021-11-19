/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:08:50 by nferre            #+#    #+#             */
/*   Updated: 2021/11/19 10:05:07 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	show_env(char *str, char **env)
{
	int	i;
	char	*check;

	check = "env";
	i = -1;
	while (++i != 3)
	{
		if (str[i] != check[i])
			return (0);
	}
	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	return (1);
}
