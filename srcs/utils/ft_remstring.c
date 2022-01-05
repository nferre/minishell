/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remstring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:01:25 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/05 17:20:40 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

// ft_remstring delete the string from the index i to index j
// and send back a string without it
// if an error occur return NULL
char	*ft_remstring(char *str, int i, int j)
{
	int		k;
	char	*ret;
	char	*tmp;

	k = i;
	ret = ft_strdup(str);
	while (k < j)
	{
		tmp = ft_remchar(ret, i);
		free(ret);
		ret = tmp;
		k++;
	}
	return (ret);
}