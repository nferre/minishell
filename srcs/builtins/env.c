/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:08:50 by nferre            #+#    #+#             */
/*   Updated: 2022/01/08 16:41:26 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*show_env(t_token **tab, char **env, int *j, char *to_print)
{
	int	i;
	char	*check;
	char	*str;
	char	*temp;
	char	*temp2;

	check = "env";
	i = -1;
	while (++i != 3)
		if (tab[0]->value[i] != check[i])
			return (to_print);
	str = malloc(sizeof(char));
	str[0] = '\0';
	i = -1;
	while (env[++i])
	{
		if (i != 0)
		{
			temp2 = ft_strdup(str);
			if (env[i][0] != '\0')
				temp = ft_strjoin(temp2, "\n");
			else
				temp = ft_strdup(temp2);
			//if (ft_strncmp(env[i], "7ca7486dfc94b", 13) != 0)
			//	temp = ft_strjoin(temp2, "\n");
			//else
			//	temp = ft_strdup(temp2);
			free(temp2);
		}
		else
			temp = ft_strdup(str);
		free(str);
		if (env[i][0] != '\0')
			str = ft_strjoin(temp, env[i]);
		else
			str = ft_strdup(temp);
		//if (ft_strncmp(env[i], "7ca7486dfc94b", 13) != 0)
		//	str = ft_strjoin(temp, env[i]);
		//else
		//	str = ft_strdup(temp);
		free(temp);
	}
	temp = ft_strjoin(str, "\n");
	*j += 1;
	free(str);
	return (temp);
}
