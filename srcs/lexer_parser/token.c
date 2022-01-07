/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:33:30 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/07 17:00:47 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include <stdlib.h>

t_token	*init_token(int type, char *value, int expanded)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->e_type = type;
	token->value = value;
	token->expanded = expanded;
	return (token);
}

void	destroy_token(t_token *token)
{
	free(token->value);
	free(token);
}