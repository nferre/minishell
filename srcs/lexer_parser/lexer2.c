/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:44:28 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/14 15:00:00 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"

t_token	*lexer_collect_quote_string(t_lexer *lexer)
{
	char	*value;
	int		j;
	int		i;
	int		reset_i;

	reset_i = lexer->i;
	lexer_advance(lexer);
	j = 0;
	i = lexer->i;
	while ((lexer->c && lexer->i < ft_strlen(lexer->contents)) && (lexer->c != '\''))
	{
		j++;
		lexer_advance(lexer);
	}
	if (lexer->i == ft_strlen(lexer->contents))
	{
		lexer->i = reset_i;
		lexer->c = lexer->contents[reset_i];
		return (lexer_collect_arg(lexer));
	}
	lexer_advance(lexer);
	value = ft_strndup(lexer->contents + i, j);
	return (init_token(TOKEN_QUOTE_STRING, value, 0));
}

t_token	*lexer_collect_double_quote_string(t_lexer *lexer)
{
	char	*value;
	int		j;
	int		i;
	int		reset_i;

	reset_i = lexer->i;
	lexer_advance(lexer);
	j = 0;
	i = lexer->i;
	while ((lexer->c && lexer->i < ft_strlen(lexer->contents)) && (lexer->c != '\"'))
	{
		j++;
		lexer_advance(lexer);
	}
	if (lexer->i == ft_strlen(lexer->contents))
	{
		lexer->i = reset_i;
		lexer->c = lexer->contents[reset_i];
		return (lexer_collect_arg(lexer));
	}
	lexer_advance(lexer);
	value = ft_strndup(lexer->contents + i, j);
	return (init_token(TOKEN_DOUBLE_QUOTE_STRING, value, 0));
}

t_token	*lexer_collect_arg(t_lexer *lexer)
{
	char	*value;
	char	*tmp_value;
	char	*tmp;
	char	*tmp2;
	t_token	*tok;
	t_lexer	*tmp_lexer;
	int		i;
	int		j;
	int		tmp_minus_value;

	i = lexer->i;
	j = 0;
	while ((lexer->c && (lexer->i < ft_strlen(lexer->contents))) && !ft_isspace(lexer->c) && !lexer_is_operand(lexer))
	{
		j++;
		lexer_advance(lexer);
	}
	value = ft_strndup((lexer->contents + i), j);
	tmp = ft_strchr(value, '\"');
	tmp_minus_value = tmp - value;
	if (tmp)
	{
		tmp2 = ft_strchr(tmp + 1, '\"');
		if (value != tmp && value != tmp && *(tmp - 1) == '$')
		{
			tmp_value = ft_remchar(value, tmp_minus_value - 1);
			free(value);
			value = tmp_value;
		}
		if (tmp2)
		{
			tmp_lexer = init_lexer(lexer->contents);
			tmp_lexer->i = tmp_minus_value + i;
			tmp_lexer->c = tmp_lexer->contents[tmp_lexer->i];
			tok = lexer_collect_double_quote_string(tmp_lexer);
			tok = expand_token(tok);
			tmp_value = ft_remstring(value, tmp - value, tmp2 - value + 1);
			free(value);
			value = tmp_value;
			value = ft_strjoin_free_null(value, tok->value);
			destroy_token(tok);
			free(tmp_lexer);
			return (init_token(TOKEN_ARG, value, 1));
		}
	}
	tmp = ft_strchr(value, '\'');
	tmp_minus_value = tmp - value;
	if (tmp)
	{
		tmp2 = ft_strchr(tmp + 1, '\'');
		if (value != tmp && value != tmp && *(tmp - 1) == '$')
		{
			tmp_value = ft_remchar(value, tmp_minus_value - 1);
			free(value);
			value = tmp_value;
		}
		if (tmp2)
		{
			tmp_lexer = init_lexer(lexer->contents);
			tmp_lexer->i = tmp_minus_value + i;
			tmp_lexer->c = tmp_lexer->contents[tmp_lexer->i];
			tok = lexer_collect_quote_string(tmp_lexer);
			tmp_value = ft_remstring(value, tmp - value, tmp2 - value + 1);
			free(value);
			value = tmp_value;
			value = ft_strjoin_free_null(value, tok->value);
			return (init_token(TOKEN_ARG, value, 1));
		}
	}
	return (init_token(TOKEN_ARG, value, 0));
}

t_token	*lexer_collect_var(t_lexer *lexer)
{
	char	*value;
	int		i;
	int		j;

	// lexer_advance(lexer);
	i = lexer->i;
	j = 0;
	while ((lexer->c && (lexer->i < ft_strlen(lexer->contents))) && !ft_isspace(lexer->c))
	{
		j++;
		lexer_advance(lexer);
	}
	value = ft_strndup((lexer->contents + i), j);
	return (init_token(TOKEN_ENV_VAR, value, 0));
}