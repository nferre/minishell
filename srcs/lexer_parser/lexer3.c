/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:08:03 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/06 19:09:51 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "token.h"
#include "libft.h"

// Init the escaped character list of the lexer
// If list[i] == 1 char is escaped otherwise its not
int	*lexer_init_escape_list(char **contents)
{
	int		*list;
	char	*tmp_contents;
	int		begin_contents_size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	begin_contents_size = ft_strlen_null(*contents);
	list = malloc(sizeof(int) * begin_contents_size);
	while (*contents && (i < ft_strlen_null(*contents)))
	{
		if (((i > 0) && i < ft_strlen_null(*contents)) && ((*contents)[i - j - 1] == '\\'))
		{
			list[i - j] = 1;
			tmp_contents = ft_remchar(*contents, i - j - 1);
			free(*contents);
			*contents = tmp_contents;
			j++;
		}
		else
			list[i - j] = 0;
		i++;
	}
	while (i < begin_contents_size)
		list[i++] = 0;
	return (list);
}