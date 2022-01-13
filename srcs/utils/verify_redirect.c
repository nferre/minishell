/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:41:13 by nferre            #+#    #+#             */
/*   Updated: 2022/01/13 18:56:52 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_redirect(t_token **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if ((tab[i]->e_type == TOKEN_REDIRECT_OUT || tab[i]->e_type == TOKEN_REDIRECT_OUT_APPEND) && (tab[i + 1] == NULL))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	return (0);
}
