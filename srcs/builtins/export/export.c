/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 10:13:39 by nferre            #+#    #+#             */
/*   Updated: 2022/01/12 15:38:11 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*nb_to_malloc(char *str, int i, char c)
{
	char	*malloc_me;
	int	j;

	j = 0;
	while (ft_isspace(str[i]) == 0 && str[i] && str[i] != c)
	{
		j++;
		i++;
	}
	malloc_me = malloc(sizeof(char) * (j + 1));
	return (malloc_me);
}

char	*get_name(t_token **tab, int i_to_exec)
{
	char	*data_name;
	int	i;
	int	j;

	j = 0;
	i = 0;
	data_name = nb_to_malloc(tab[1 + i_to_exec]->value, i, '=');
	while (tab[1 + i_to_exec]->value[i] != '=')
		data_name[j++] = tab[1 + i_to_exec]->value[i++];
	data_name[j] = '\0';
	return (data_name);
}

char	*get_var(t_token **tab, int i_to_exec)
{
	int	i;
	int	j;
	char	*data;

	j = 0;
	i = 0;
	while (tab[i_to_exec + 1]->value[i] != '=')
		i++;
	i++;
	data = nb_to_malloc(tab[i_to_exec + 1]->value, i, 0);
	while (tab[i_to_exec + 1]->value[i])
		data[j++] = tab[i_to_exec + 1]->value[i++];
	data[j] = '\0';
	return (data);
}

int	export_var(t_token **tab, char **env, int i_to_exec)
{
	char	*data_name;
	char	*data;
	int		i;

	i = -1;
	if (check_export(tab, i_to_exec) == 1)
		return (0);
	if (tab[i_to_exec + 1] == NULL)
	{
		while (g_data.env[++i])
			if (g_data.env[i][0] != '\0')
				printf("declare -x %s\n", g_data.env[i]);
		return (6);
	}
	if (check_arg(tab, i_to_exec) == 1)
		return (0);
	data_name = get_name(tab, i_to_exec);
	if (get_local_var(env, data_name))
		del_elem_env(env, data_name);
	data = get_var(tab, i_to_exec);
	env = add_elem_env(env, data, data_name);
	free(data);
	free(data_name);
	return (6);
}
