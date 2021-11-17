/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:39:21 by nferre            #+#    #+#             */
/*   Updated: 2021/11/17 13:47:15 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		len_s1;
	int		len_s2;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	dest = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (dest == NULL)
		return (dest);
	while (s1[++i])
		dest[i] = s1[i];
	while (*(s2))
		dest[i++] = *(s2++);
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*copy_s1;
	int		i;

	if (!src)
		return (0);
	copy_s1 = malloc(ft_strlen((char *)src) + 1);
	if (copy_s1 == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		copy_s1[i] = src[i];
		i++;
	}
	copy_s1[i] = '\0';
	return (copy_s1);
}
