/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:04:29 by nferre            #+#    #+#             */
/*   Updated: 2021/11/29 15:01:04 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**dup_env(char **env, char *data, char *data_name)
{
	int	i;
	int	j;
	char	*temp;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	temp = malloc((ft_strlen(data) + ft_strlen(data_name) + 2) * sizeof(char));
	free(temp);
	return (env);
}

char	**add_elem_env(char **env, char *data, char *data_name)
{
	int	i;
	char	*temp;

	i = 0;
	env = dup_env(env, data, data_name);
	while (env[i])
		i++;
	temp = ft_strjoin(data_name, "=");
	env[i] = ft_strjoin(temp, data);
	env[i + 1] = NULL;
	free(temp);
	return (env);
}
