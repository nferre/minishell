/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:51:41 by hadufer           #+#    #+#             */
/*   Updated: 2021/11/27 09:44:16 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
int	ft_isspace(int c)
{
	if ((c == 0x20 || c == 0x09) || (c == 0x0a || c == 0x0b)
		|| (c == 0x0c || c == 0x0d))
		return (1);
	return (0);
}
