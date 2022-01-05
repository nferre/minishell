/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:29:27 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/05 18:19:19 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"

t_lexer	*init_lexer(char *contents)
{
	t_lexer	*lexer = ft_calloc(1, sizeof(t_lexer));
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
			return (lexer_advance_with_token(lexer, init_token(TOKEN_REDIRECT_IN_HEREDOC, ft_strdup("<<"))));
		}
		else if (ft_strncmp(lexer->contents + lexer->i, ">>", 2) == 0)
		{
			lexer_advance(lexer);
			lexer_advance(lexer);
			return (lexer_advance_with_token(lexer, init_token(TOKEN_REDIRECT_OUT_APPEND, ft_strdup(">>"))));
		}
		else if (lexer->c == '<')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_REDIRECT_IN, lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == '>')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_REDIRECT_OUT, lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == '|')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_PIPE, lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == ';')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_SEMICOLON, lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == '\'')
			return (lexer_advance_with_token(lexer, lexer_collect_quote_string(lexer)));
		else if (lexer->c == '\"')
			return (lexer_advance_with_token(lexer, lexer_collect_double_quote_string(lexer)));
		// else if (lexer->c == '$')
		// 	return (lexer_advance_with_token(lexer, lexer_collect_var(lexer)));
		else
			return (lexer_advance_with_token(lexer, lexer_collect_arg(lexer)));
	}
	return (NULL);
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

char	*lexer_get_current_char_as_string(t_lexer *lexer)
{
	char	*str = ft_calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = 0;
	return (str);
}
