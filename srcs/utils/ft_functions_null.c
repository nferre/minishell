/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions_null.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:12:26 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/07 17:02:28 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t	ft_strlen_null(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_null(char *s1, char *s2)
{
	char	*ret;
	size_t	i;

	ret = malloc((ft_strlen_null(s1) + ft_strlen_null(s2) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s1 && *s1)
	{
		ret[i] = *s1;
		i++;
		s1++;
	}
	while (s2 && *s2)
	{
		ret[i] = *s2;
		i++;
		s2++;
	}
	ret[i] = 0;
	return (ret);
}

char	*ft_strjoin_free_null(char *s1, char *s2)
{
	char	*ret;
	char	*tmp;
	size_t	i;

	tmp = s1;
	ret = malloc((ft_strlen_null(s1) + ft_strlen_null(s2) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s1 && *s1)
	{
		ret[i] = *s1;
		i++;
		s1++;
	}
	while (s2 && *s2)
	{
		ret[i] = *s2;
		i++;
		s2++;
	}
	free(tmp);
	ret[i] = 0;
	return (ret);
}
