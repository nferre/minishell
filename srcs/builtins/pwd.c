/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:31:31 by nferre            #+#    #+#             */
/*   Updated: 2021/12/02 10:43:54 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*pwd(t_token **tab, int *j, char *to_print)
{
	int	i;
	char	*pwd;
	char	*str;
	char	cwd[PATH_MAX];
	char	*temp;

	pwd = "pwd";
	i = 0;
	while (tab[0]->value[i] == ' ')
		i++;
	while (++i != 3)
		if (pwd[i] != tab[0]->value[i])
			return (to_print);
	str = ft_strdup(getcwd(cwd, sizeof(cwd)));
	temp = ft_strjoin(str, "\n");
	free(str);
	*j += 1;
	return (temp);
}
