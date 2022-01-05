/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:12:14 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/05 17:28:47 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

// Insert needle string into at the index k of haystack and return the result
char	*ft_insert_string(char *haystack, char *needle, int k)
{
	int		i;
	char	*tmp;
	char	*tmp_begin;
	char	*tmp_end;
	char	*ret;

	i = 0;
	ret = NULL;
	if (!haystack || !needle)
		return (NULL);
	while (haystack[i] && (i < k))
		i++;
	tmp_begin = ft_strndup(haystack, i);
	tmp_end = ft_strndup(haystack + i, ft_strlen(haystack) - i);
	tmp = ft_strjoin_null(tmp_begin, needle);
	ret = ft_strjoin_null(tmp, tmp_end);
	return (ret);
}