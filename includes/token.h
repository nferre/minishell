/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:49:09 by hadufer           #+#    #+#             */
/*   Updated: 2021/12/01 14:11:48 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_token
{
	enum
	{
		TOKEN_ARG,
		TOKEN_REDIRECT_OUT,
		TOKEN_REDIRECT_IN,
		TOKEN_REDIRECT_IN_HEREDOC,
		TOKEN_REDIRECT_OUT_APPEND,
		TOKEN_PIPE,
		TOKEN_SEMICOLON,
		TOKEN_QUOTE_STRING,
		TOKEN_DOUBLE_QUOTE_STRING,
		TOKEN_ENV_VAR,
		TOKEN_EXPAND_EXIT_STATUS
	} e_type;
	char	*value;
}			t_token;

t_token	*init_token(int type, char *value);
#endif
