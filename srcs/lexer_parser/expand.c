/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:36:00 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/15 18:30:05 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"

// Utility function to delete char i from token token
t_token	*remove_char_from_token(t_token *token, int i)
{
	char		*tmp;
	t_token		*tmp_token;

	tmp = ft_remchar(token->value, i);
	tmp_token = init_token(token->e_type, tmp, token->expanded);
	destroy_token(token);
	return (tmp_token);
}

int	expand_token_utils(t_token *token, int *i, int *j, int *k)
{
	if (token->value[*i] == '$')
	{
		++(*j);
		if (!token->value[*i + *j] || (token->value[*i + *j]
				&& token->value[*i + *j] == '$'))
			return (1);
		if (token->value[*i + *j] == '?')
			*k = 1;
		while (token->value[*i + *j]
			&& !ft_isspace(token->value[*i + *j])
			&& token->value[*i + *j] != '$')
			(*j)++;
	}
	return (0);
}

void	expand_token_utils2(t_token *token, char *tab[3], int *it)
{
	tab[0] = ft_strndup(token->value + (it[0]) + 1, (it[1]) - 1);
	if (!(it[2]))
	{
		tab[1] = get_local_var(g_data.env, tab[0]);
		if (!tab[1])
			tab[1] = ft_strdup("");
	}
	else
	{
		tab[1] = ft_itoa(g_data.last_exit_status);
		(it[2]) = 0;
	}
	tab[2] = ft_remstring(token->value, (it[0]), (it[0]) + (it[1]));
	free(token->value);
	token->value = tab[2];
	tab[2] = ft_insert_string(token->value, tab[1], (it[0]));
	free(token->value);
	token->value = tab[2];
	free(tab[0]);
	token->expanded = 1;
	(it[1]) = 0;
	(it[0]) = 0;
}

t_token	*expand_token(t_token *token)
{
	int		it[3];
	char	*tab[3];

	it[0] = 0;
	it[1] = 0;
	it[2] = 0;
	if (((token && token->value) && !token->expanded)
		&& ((token->e_type == TOKEN_DOUBLE_QUOTE_STRING)
			|| (token->e_type == TOKEN_ARG)
			|| (token->e_type == TOKEN_ENV_VAR)))
	{
		while ((token->value && token->value[it[0]]))
		{
			if (expand_token_utils(token, &it[0], &it[1], &it[2]) == 1)
				break ;
			if (it[1] > 0)
				expand_token_utils2(token, tab, it);
			it[0]++;
		}
	}
	return (token);
}
