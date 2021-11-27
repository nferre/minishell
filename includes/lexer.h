/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:36:26 by hadufer           #+#    #+#             */
/*   Updated: 2021/11/25 11:17:22 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "token.h"

typedef struct s_lexer
{
	char			c;
	unsigned int	i;
	char			*contents;
}				t_lexer;

// LEXER PARSER
t_lexer	*init_lexer(char *contents);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespace(t_lexer *lexer);
t_token	*lexer_get_next_token(t_lexer *lexer);
t_token	*lexer_collect_quote_string(t_lexer *lexer);
t_token	*lexer_collect_double_quote_string(t_lexer *lexer);
t_token	*lexer_collect_arg(t_lexer *lexer);
char	*lexer_get_current_char_as_string(t_lexer *lexer);
t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token);
#endif
