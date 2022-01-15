/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:44:28 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/15 16:09:05 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"

t_token	*lexer_collect_arg_util(t_lexer *lexer, char **tab, int *it)
{
	t_token	*tok;
	t_lexer	*t;

	t = init_lexer(lexer->contents);
	tok = NULL;
	(t)->i = it[2] + it[0];
	(t)->c = (t)->contents[(t)->i];
	tok = lexer_collect_double_quote_string((t));
	tok = expand_token(tok);
	tab[1] = ft_remstring(tab[0], tab[2] - tab[0], tab[3] - tab[0] + 1);
	free(tab[0]);
	tab[0] = tab[1];
	tab[0] = ft_strjoin_free_null(tab[0], tok->value);
	destroy_token(tok);
	free((t));
	return (init_token(TOKEN_ARG, tab[0], 1));
}

t_token	*lexer_collect_arg_util2(t_lexer *lexer, char **tab, int *it)
{
	t_token	*tok;
	t_lexer	*t;

	t = init_lexer(lexer->contents);
	tok = NULL;
	(t)->i = it[2] + it[0];
	(t)->c = (t)->contents[(t)->i];
	tok = lexer_collect_quote_string((t));
	tab[1] = ft_remstring(tab[0], tab[2] - tab[0], tab[3] - tab[0] + 1);
	free(tab[0]);
	tab[0] = tab[1];
	tab[0] = ft_strjoin_free_null(tab[0], tok->value);
	return (init_token(TOKEN_ARG, tab[0], 1));
}

void	lexer_collect_arg_util_begin(t_lexer *lexer, char **tab, int *it)
{
	while ((lexer->c && (lexer->i < ft_strlen(lexer->contents)))
		&& !ft_isspace(lexer->c) && !lexer_is_operand(lexer))
	{
		it[1]++;
		lexer_advance(lexer);
	}
	tab[0] = ft_strndup((lexer->contents + it[0]), it[1]);
	tab[2] = ft_strchr(tab[0], '\"');
}

t_token	*lexer_collect_quote_arg(t_lexer *lexer, char **tab, int *it)
{
	tab[2] = ft_strchr(tab[0], '\'');
	it[2] = tab[2] - tab[0];
	if (tab[2])
	{
		tab[3] = ft_strchr(tab[2] + 1, '\'');
		if (tab[0] != tab[2] && tab[0] != tab[2] && *(tab[2] - 1) == '$')
		{
			tab[1] = ft_remchar(tab[0], it[2] - 1);
			free(tab[0]);
			tab[0] = tab[1];
		}
		if (tab[3])
			return (lexer_collect_arg_util2(lexer, tab, it));
	}
	return (NULL);
}

t_token	*lexer_collect_arg(t_lexer *lexer)
{
	char		*tab[4];
	const int	it[3] = {lexer->i, 0};
	t_token		*tok;

	if (!lexer->c)
		return (NULL);
	lexer_collect_arg_util_begin(lexer, tab, (int *)it);
	((int *)it)[2] = tab[2] - tab[0];
	if (tab[2])
	{
		tab[3] = ft_strchr(tab[2] + 1, '\"');
		if (tab[0] != tab[2] && tab[0] != tab[2] && *(tab[2] - 1) == '$')
		{
			tab[1] = ft_remchar(tab[0], it[2] - 1);
			free(tab[0]);
			tab[0] = tab[1];
		}
		if (tab[3])
			return (lexer_collect_arg_util(lexer, tab, (int *)it));
	}
	tok = lexer_collect_quote_arg(lexer, tab, (int *)it);
	if (tok)
		return (tok);
	return (init_token(TOKEN_ARG, tab[0], 0));
}
