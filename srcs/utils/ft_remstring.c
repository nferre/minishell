/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remstring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:01:25 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/15 13:08:16 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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
