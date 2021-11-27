/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 10:13:39 by nferre            #+#    #+#             */
/*   Updated: 2021/11/27 13:35:20 by nferre           ###   ########.fr       */
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

char	*get_name(char *str)
{
	char	*data_name;
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	while (ft_isspace(str[i]) == 0)
		i++;
	while (ft_isspace(str[i]) == 1)
		i++;
	data_name = nb_to_malloc(str, i, '=');
	while (ft_isspace(str[i]) == 0 && str[i] != '=')
		data_name[j++] = str[i++];
	data_name[j] = '\0';
	return (data_name);
}

char	*get_var(char *str)
{
	int	i;
	int	j;
	char	*data;

	j = 0;
	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	data = nb_to_malloc(str, i, 0);
	while (str[i] && ft_isspace(str[i]) == 0)
		data[j++] = str[i++];
	data[j] = '\0';
	return (data);
}

int	export_var(char *str, char **env)
{
	char	*data_name;
	char	*data;

	if (verify(str) == 1)
		return (0);
	data_name = get_name(str);
	data = get_var(str);
	(void)env;
	return (1);
}
