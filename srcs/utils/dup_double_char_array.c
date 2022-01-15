/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_double_char_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:48:18 by nferre            #+#    #+#             */
/*   Updated: 2022/01/15 13:05:57 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_token	**dup_double_token_array(t_token **tab)
{
	int		i;
	t_token	**new_tab;

	i = 0;
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(t_token *) * (i + 1));
	i = -1;
	while (tab[++i])
	{
		new_tab[i] = malloc(sizeof(t_token));
		new_tab[i]->e_type = tab[i]->e_type;
		new_tab[i]->value = ft_strdup(tab[i]->value);
	}
	new_tab[i] = NULL;
	return (new_tab);
}
