/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:29:27 by hadufer           #+#    #+#             */
/*   Updated: 2021/11/25 09:47:46 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

// Initialize the lexer
t_lexer	*init_lexer(char *contents)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return (lexer);
}

// Advance lexer to the next character
void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c && (lexer->i < ft_strlen(lexer->contents)))
	{
		(lexer->i)++;
		lexer->c = lexer->contents[lexer->i];
	}
}

// If lexer->c isspace then lexer advance
void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (ft_isspace(lexer->c))
	{
		lexer_advance(lexer);
	}
}

//
t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c && (lexer->i < ft_strlen(lexer->contents)))
	{
		if (ft_isspace(lexer->c))
			lexer_skip_whitespace(lexer);

		if (lexer->c == "<")
			return (lexer_advance_with_token(lexer, init_token(TOKEN_REDIRECT_IN, lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == ">")
			return (lexer_advance_with_token(lexer, init_token(TOKEN_REDIRECT_OUT, lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == "<<")
			return (lexer_advance_with_token(lexer, init_token(TOKEN_REDIRECT_IN_HEREDOC, lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == ">>")
			return (lexer_advance_with_token(lexer, init_token(TOKEN_REDIRECT_OUT_APPEND, lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == "|")
			return (lexer_advance_with_token(lexer, init_token(TOKEN_PIPE, lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == ";")
			return (lexer_advance_with_token(lexer, init_token(TOKEN_SEMICOLON, lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == "\'")
			return (lexer_advance_with_token(lexer, init_token(TOKEN_QUOTE_STRING, lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == "\"")
			return (lexer_advance_with_token(lexer, init_token(TOKEN_DOUBLE_QUOTE_STRING, lexer_get_current_char_as_string(lexer))));
		ft_strcmp("");
		// TOKEN ENV_VAR TO DO
		// TOKEN EXPAND_EXIT_STATUS
	}
}

t_token	*lexer_advance_with_token(lexer_t *lexer, token_t *token)
{

}
t_token	lexer_collect_string(t_lexer *lexer);
char	*lexer_get_current_char_as_string(t_lexer *lexer);
