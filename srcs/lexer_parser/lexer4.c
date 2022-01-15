/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:35:55 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/15 14:45:33 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"

t_lexer	*init_lexer(char *contents)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (ft_isspace(lexer->c))
		lexer_advance(lexer);
}

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
	while ((lexer->c && lexer->i < ft_strlen(lexer->contents))
		&& (lexer->c != '\''))
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
	while ((lexer->c && lexer->i < ft_strlen(lexer->contents))
		&& (lexer->c != '\"'))
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
