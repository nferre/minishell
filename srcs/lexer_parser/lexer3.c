/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:22:48 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/15 14:35:03 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"
#include "token.h"

int	lexer_is_operand(t_lexer *lexer)
{
	size_t	i;

	i = lexer->i;
	if (lexer->contents[i] == '>' && (i + 1 < ft_strlen_null(lexer->contents))
		&& lexer->contents[i + 1] == '>')
		return (1);
	else if (lexer->contents[i] == '<'
		&& (i + 1 < ft_strlen_null(lexer->contents))
		&& lexer->contents[i + 1] == '<')
		return (1);
	else if (lexer->contents[i] == '<')
		return (1);
	else if (lexer->contents[i] == '>')
		return (1);
	else if (lexer->contents[i] == '|')
		return (1);
	return (0);
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

char	*lexer_get_current_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = 0;
	return (str);
}

t_token	*lexer_collect_var(t_lexer *lexer)
{
	char	*value;
	int		i;
	int		j;

	i = lexer->i;
	j = 0;
	while ((lexer->c && (lexer->i < ft_strlen(lexer->contents)))
		&& !ft_isspace(lexer->c))
	{
		j++;
		lexer_advance(lexer);
	}
	value = ft_strndup((lexer->contents + i), j);
	return (init_token(TOKEN_ENV_VAR, value, 0));
}
