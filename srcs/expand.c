/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:12:58 by nferre            #+#    #+#             */
/*   Updated: 2021/12/22 10:26:19 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

char	*get_local_var(char **env, char *str)
{
	char	*final_str;
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
	final_str = malloc(sizeof(char));
	final_str[0] = '\0';
	return (final_str);
}
