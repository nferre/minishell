/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:12:58 by nferre            #+#    #+#             */
/*   Updated: 2022/01/15 13:22:57 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "token.h"

char	*get_local_var(char **env, char *str)
{
	int	i;
	int	j;
	int	ver;

	i = -1;
	while (env[++i])
	{
		j = 0;
		ver = 1;
		while (env[i][j] && str[j])
		{
			if (env[i][j] != str[j])
			{
				ver = 0;
				break ;
			}
			j++;
		}
		if (ver == 1)
			return (env[i] + j + 1);
	}
	return (NULL);
}

int	get_line_local_var(char **env, char *str)
{
	int	i;

	i = -1;
	while (env[++i])
		if (strncmp(env[i], str, ft_strlen(str)) == 0)
			return (i);
	return (-1);
}
