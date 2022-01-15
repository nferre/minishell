/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:01:37 by nferre            #+#    #+#             */
/*   Updated: 2022/01/15 13:01:26 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_n(char *str)
{
	int	i;

	if (str[0] != '-' || str[1] != 'n')
		return (0);
	i = 1;
	while (str[i] == 'n')
		++i;
	if (str[i] != '\0')
		return (0);
	return (-1);
}

char	*get_str_to_print(t_token **tab, int i)
{
	char	*final_str;
	char	*temp;

	final_str = ft_strdup(tab[i]->value);
	i++;
	while (tab[i])
	{
		if (tab[i]->e_type == 0 || tab[i]->e_type == 7)
		{
			temp = ft_strjoin(" ", tab[i]->value);
			final_str = ft_strjoin_free(final_str, temp);
			free(temp);
			i++;
		}
		else
			break ;
	}
	return (final_str);
}

int	print_str(t_token **tab, int i_to_exec, char *to_print)
{
	to_print = get_str_to_print(tab, i_to_exec + 1);
	printf("%s\n", to_print);
	free(to_print);
	return (1);
}

int	echo(t_token **tab, int i_to_exec)
{
	char	*echo;
	int		i;
	int		ver;
	char	*to_print;

	i = -1;
	ver = 0;
	echo = "echo";
	while (++i != 5)
		if (tab[i_to_exec]->value[i] != echo[i])
			return (0);
	if (tab[i_to_exec + 1] == NULL || tab[i_to_exec + 1]->e_type != TOKEN_ARG)
	{
		printf("\n");
		return (1);
	}
	if (check_n(tab[i_to_exec + 1]->value) == 0)
		return (print_str(tab, i_to_exec, to_print));
	if (tab[i_to_exec + 2])
		to_print = get_str_to_print(tab, i_to_exec + 2);
	else
		return (1);
	printf("%s", to_print);
	free(to_print);
	return (1);
}
