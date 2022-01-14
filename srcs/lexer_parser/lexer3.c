/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:22:48 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/14 14:57:53 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"
#include "token.h"

int	lexer_is_operand(t_lexer *lexer)
{
	int	i;

	i = lexer->i;
	if (lexer->contents[i] == '>' && (i + 1 < ft_strlen_null(lexer->contents)) && lexer->contents[i + 1] == '>')
		return (1);
	else if (lexer->contents[i] == '<' && (i + 1 < ft_strlen_null(lexer->contents)) && lexer->contents[i + 1] == '<')
		return (1);
	else if (lexer->contents[i] == '<')
		return (1);
	else if (lexer->contents[i] == '>')
		return (1);
	else if (lexer->contents[i] == '|')
		return (1);
	return (0);
}