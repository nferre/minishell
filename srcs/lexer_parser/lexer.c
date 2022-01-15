/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:29:27 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/15 14:45:04 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "token.h"

t_token	*lexer_get_next_token_util(t_lexer *lexer)
{
	if (lexer->c == '<')
		return (lexer_advance_with_token(lexer, init_token(TOKEN_REDIRECT_IN,
					lexer_get_current_char_as_string(lexer), 0)));
	else if (lexer->c == '>')
		return (lexer_advance_with_token(lexer, init_token(TOKEN_REDIRECT_OUT,
					lexer_get_current_char_as_string(lexer), 0)));
	else if (lexer->c == '|')
		return (lexer_advance_with_token(lexer, init_token(TOKEN_PIPE,
					lexer_get_current_char_as_string(lexer), 0)));
	else if (lexer->c == '\'')
		return (lexer_collect_quote_string(lexer));
	else if (lexer->c == '\"')
		return (lexer_collect_double_quote_string(lexer));
	else
		return (lexer_collect_arg(lexer));
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c && (lexer->i < ft_strlen(lexer->contents)))
	{
		if (ft_isspace(lexer->c))
			lexer_skip_whitespace(lexer);
		if (ft_strncmp(lexer->contents + lexer->i, "<<", 2) == 0)
		{
			lexer_advance(lexer);
			lexer_advance(lexer);
			return (lexer_advance_with_token(lexer,
					init_token(TOKEN_REDIRECT_IN_HEREDOC, ft_strdup("<<"), 0)));
		}
		else if (ft_strncmp(lexer->contents + lexer->i, ">>", 2) == 0)
		{
			lexer_advance(lexer);
			lexer_advance(lexer);
			return (lexer_advance_with_token(lexer,
					init_token(TOKEN_REDIRECT_OUT_APPEND, ft_strdup(">>"), 0)));
		}
		return (lexer_get_next_token_util(lexer));
	}
	return (NULL);
}
