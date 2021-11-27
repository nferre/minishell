/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:36:36 by hadufer           #+#    #+#             */
/*   Updated: 2021/11/25 12:41:15 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*ret;

	i = 0;
	ret = ft_calloc(sizeof(char), n + 1);
	while (str[i] && i < n)
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}
