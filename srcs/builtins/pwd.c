/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:31:31 by nferre            #+#    #+#             */
/*   Updated: 2022/01/15 13:03:28 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	pwd(t_token **tab, int i_to_exec)
{
	int		i;
	char	*pwd;
	char	cwd[PATH_MAX];

	pwd = "pwd";
	i = 0;
	while (tab[i_to_exec]->value[i] == ' ')
		i++;
	while (++i != 4)
		if (pwd[i] != tab[i_to_exec]->value[i])
			return (0);
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	return (4);
}
