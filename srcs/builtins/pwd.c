/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:31:31 by nferre            #+#    #+#             */
/*   Updated: 2022/01/11 18:36:10 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	pwd(t_token **tab)
{
	int	i;
	char	*pwd;
	char	cwd[PATH_MAX];

	pwd = "pwd";
	i = 0;
	while (tab[0]->value[i] == ' ')
		i++;
	while (++i != 3)
		if (pwd[i] != tab[0]->value[i])
			return (0);
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	return (1);
}
