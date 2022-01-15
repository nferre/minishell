/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:04:29 by nferre            #+#    #+#             */
/*   Updated: 2022/01/15 17:25:51 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	del_elem_env(char **env, char *data_name)
{
	int		line;

	line = get_line_local_var(env, data_name);
	if (line == -1)
		return ;
	env[line][0] = '\0';
}

char	**add_elem_env(char **env, char *data, char *data_name)
{
	int		i;
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
