/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 10:31:18 by nferre            #+#    #+#             */
/*   Updated: 2021/11/27 13:04:17 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int check_export(char *str, int *i)
{
	char	*export;

	export = "export";
	while (ft_isspace(str[*i]) == 1)
		*i += 1;
	while (export[*i])
	{
		if (str[*i] != export[*i] || str[*i] == '\0')
			return (1);
		*i += 1;
	}
	if (str[*i] != ' ')
		return (1);
	return (0);
}

int	check_name(char *str, int *i)
{
	while (ft_isspace(str[*i]) == 1)
		*i += 1;
	while (str[*i] != '=')
	{
		if (str[*i] == '\0' || ft_isspace(str[*i]) == 1)
			return (1);
		*i += 1;
	}
	return (0);
}

int	check_data(char *str, int *i)
{
	*i += 1;
	while (str[*i])
	{
		*i += 1;
		if (ft_isspace(str[*i]) == 1)
		{
			while (str[*i])
			{
				if (ft_isspace(str[*i]) == 0)
					return (1);
				*i += 1;
			}
		}
	}
	return (0);
}

int	verify(char *str)
{
	int	i;
	
	i = 0;
	if (check_export(str, &i) == 1)
		return (1);
	if (check_name(str, &i) == 1)
		return (1);
	if (check_data(str, &i) == 1)
		return (1);
	return (0);
}
