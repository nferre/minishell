/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:44:28 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/06 17:11:24 by hadufer          ###   ########.fr       */
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
	return (init_token(TOKEN_QUOTE_STRING, value));
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
	return (init_token(TOKEN_DOUBLE_QUOTE_STRING, value));
}

t_token	*lexer_collect_arg(t_lexer *lexer)
{
	char	*value;
	int		i;
	int		j;

	i = lexer->i;
	j = 0;
	while ((lexer->c && (lexer->i < ft_strlen(lexer->contents))) && !ft_isspace(lexer->c))
	{
		j++;
		lexer_advance(lexer);
	}
	value = ft_strndup((lexer->contents + i), j);
	return (init_token(TOKEN_ARG, value));
}

t_token	*lexer_collect_var(t_lexer *lexer)
{
	char	*value;
	int		i;
	int		j;

	lexer_advance(lexer);
	i = lexer->i;
	j = 0;
	while ((lexer->c && (lexer->i < ft_strlen(lexer->contents))) && !ft_isspace(lexer->c))
	{
		j++;
		lexer_advance(lexer);
	}
	value = ft_strndup((lexer->contents + i), j);
	return (init_token(TOKEN_ENV_VAR, value));
}