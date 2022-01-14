/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:19:30 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/14 14:57:45 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

// Will look for c in char *s while s[i] != d
char	*ft_strchr_c_null(char *s, int c, int d)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen_null(s) + 1;
	while (i < len && s[i] != d)
	{
		if ((unsigned char)(s[i]) == (unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}