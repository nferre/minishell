/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:32:05 by nferre            #+#    #+#             */
/*   Updated: 2022/01/14 18:29:23 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_operand(t_token **tab, int token)
{
	int	i;
	int	nb_token;

	i = -1;
	nb_token = 0;
	while (tab[++i])
		if (tab[i]->e_type == token)
			nb_token++;
	return (nb_token);
}

void	print_in_fd(void)
{
	char	buf[1];
	int		ret;

	ret = 1;
	while (1)
	{
		ret = read(STDIN_FILENO, buf, 1);
		if (ret != 1)
			return ;
		printf("%c", buf[0]);
	}
}
