/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:21:35 by hadufer           #+#    #+#             */
/*   Updated: 2021/12/08 18:31:39 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

// ft_remchar delete the character at the index i
// and send back the string without it
// if an error occur return NULL
char    *ft_remchar(char *str, int i)
{
    char *str_1;
    char *str_2;
    char *ret;

	if (i > ft_strlen_null(str))
		return (NULL);
	else if (i == ft_strlen_null(str))
		return (ft_strndup(str, ft_strlen_null(str) - 1));
    str_1 = ft_strndup(str, i);
    str_2 = ft_strndup(str + i + 1, ft_strlen_null(str));
    ret = ft_strjoin_null(str_1, str_2);
    free(str_1);
    free(str_2);
    return (ret);
}