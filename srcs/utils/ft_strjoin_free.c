/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 13:50:44 by nferre            #+#    #+#             */
/*   Updated: 2022/01/15 17:17:11 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	init(char *ret, int i, char *tmp)
{
	free(tmp);
	ret[i] = 0;
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	char	*tmp;

	tmp = s1;
	if (!s1 || !s2)
		return (NULL);
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (*s1)
	{
		ret[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		ret[i] = *s2;
		i++;
		s2++;
	}
	init(ret, i, tmp);
	return (ret);
}
