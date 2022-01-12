/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:00:45 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/11 16:09:14 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "lexer.h"
#include "libft.h"

// Look for the first token of type PIPE or REDIRECT IN OR OUT HEREDOC OR APPEND
// Return 1 if operand is present 0 otherwise
int	get_first_operand_index(t_token **tab, int i_to_exec)
{
	int	i;

	i = 0;
	if (i_to_exec)
		i = i_to_exec;
	while (tab[i])
	{
		if (tab[i]->e_type == TOKEN_PIPE || tab[i]->e_type == TOKEN_REDIRECT_OUT_APPEND
			|| tab[i]->e_type == TOKEN_REDIRECT_IN_HEREDOC || tab[i]->e_type == TOKEN_REDIRECT_IN
			|| tab[i]->e_type == TOKEN_REDIRECT_OUT)
			return (i);
		i++;
	}
	return (-1);
}

// Return the number of operand left starting from i_to_exec
int	count_operand(t_token **tab, int i_to_exec)
{
	int	i;
	int	j;

	i = 0;
	if (i_to_exec)
		i = i_to_exec;
	j = 0;
	while (tab[i])
	{
		if (tab[i]->e_type == TOKEN_PIPE || tab[i]->e_type == TOKEN_REDIRECT_OUT_APPEND
			|| tab[i]->e_type == TOKEN_REDIRECT_IN_HEREDOC || tab[i]->e_type == TOKEN_REDIRECT_IN
			|| tab[i]->e_type == TOKEN_REDIRECT_OUT)
			j++;
		i++;
	}
	return (j);
}