/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:08:50 by nferre            #+#    #+#             */
/*   Updated: 2021/12/01 13:52:38 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*show_env(t_token **tab, char **env, int *j, char *to_print)
{
	int	i;
	char	*check;
	char	*str;
	char	*temp;

	check = "env";
	i = -1;
	str = malloc(sizeof(char));
	str[0] = '\0';
	while (++i != 3)
		if (tab[0]->value[i] != check[i])
			return (to_print);
	i = -1;
	while (env[++i])
	{
		if (i != 0)
			temp = ft_strjoin(ft_strdup(str), "\n");
		else
			temp = ft_strdup(str);
		free(str);
		str = ft_strjoin(temp, env[i]);
		free(temp);
	}
	temp = ft_strjoin(str, "\n");
	*j += 1;
	free(str);
	return (temp);
}
