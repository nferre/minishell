/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:04:29 by nferre            #+#    #+#             */
/*   Updated: 2022/01/06 17:29:05 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	del_elem_env(char **env, char *data_name)
{
	char	*temp;
	int		line;

	line = get_line_local_var(env, data_name);
	free(env[line]);
	env[line] = malloc(sizeof(char) * 14);
	env[line] = "7ca7486dfc94b";
}

char	**add_elem_env(char **env, char *data, char *data_name)
{
	int	i;
	char	*temp;

	i = 0;
	while (env[i])
		i++;
	temp = ft_strjoin(data_name, "=");
	env[i] = ft_strjoin(temp, data);
	env[i + 1] = NULL;
	free(temp);
	return (env);
}
