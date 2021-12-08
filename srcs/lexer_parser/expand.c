/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:36:00 by hadufer           #+#    #+#             */
/*   Updated: 2021/12/08 18:53:47 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"

t_token	*remove_char_from_token(t_token *token, int i)
{
	char 	*tmp;
	t_token *tmp_token;

	tmp = ft_remchar(token->value, i);
	tmp_token = init_token(token->e_type, tmp);
	destroy_token(token);
	return (tmp_token);
}

t_token	*expand_token(t_token *token)
{
	int	 	i;

	i = 0;
	while (token && token->value && token->value[i])
	{
		if (token->value[i] == '\'')
			token = remove_char_from_token(token, i);
		else if (token->value[i] == '\"')
			token = remove_char_from_token(token, i);
		// else if (token->value[i] == '$')
		i++;
	}
	return (NULL);
}
