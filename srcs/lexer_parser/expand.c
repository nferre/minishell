/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:36:00 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/07 17:11:19 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"

// Utility function to delete char i from token token
t_token	*remove_char_from_token(t_token *token, int i)
{
	char 	*tmp;
	t_token *tmp_token;

	tmp = ft_remchar(token->value, i);
	tmp_token = init_token(token->e_type, tmp, token->expanded);
	destroy_token(token);
	return (tmp_token);
}

t_token	*expand_token(t_token *token)
{
	int		i;
	int		j;
	int		last_exit_status;
	char	*key;
	char	*value;
	char	*tmp;

	i = 0;
	j = 0;
	last_exit_status = 0;
	if (((token && token->value) && !token->expanded) && ((token->e_type == TOKEN_DOUBLE_QUOTE_STRING) || (token->e_type == TOKEN_ARG) || (token->e_type == TOKEN_ENV_VAR)))
	{
		while ((token->value && token->value[i]))
		{
			if (token->value[i] == '$')
			{
				++j;
				if (token->value[i + j] == '?')
					last_exit_status = 1;
				while (token->value[i + j] && !ft_isspace(token->value[i + j]) && token->value[i + j] != '$')
					j++;
			}
			if (j > 0)
			{
				key = ft_strndup(token->value + i + 1, j - 1);
				if (!last_exit_status)
					value = get_local_var(g_data.env, key);
				else
				{
					value = ft_itoa(g_data.last_exit_status);
					last_exit_status = 0;
				}
				tmp = ft_remstring(token->value, i, i + j);
				free(token->value);
				token->value = tmp;
				tmp = ft_insert_string(token->value, value, i);
				free(token->value);
				token->value = tmp;
				free(key);
				token->expanded = 1;
				j = 0;
				i = 0;
			}
			i++;
		}
	}
	return (token);
}


