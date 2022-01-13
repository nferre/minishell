/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:34:08 by nferre            #+#    #+#             */
/*   Updated: 2022/01/13 15:59:29 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *str)
{
	char	*final_string;
	int		line_path;

	line_path = get_line_local_var(g_data.env, str);
	if (line_path == -1)
		return (NULL);
	final_string = ft_strdup(g_data.env[line_path] + ft_strlen(str) + 1);
	return (final_string);
}
