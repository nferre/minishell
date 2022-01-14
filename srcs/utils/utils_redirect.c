/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:32:05 by nferre            #+#    #+#             */
/*   Updated: 2022/01/14 17:55:04 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_pipe_operand(t_token **tab)
{
	int	i;
	int	nb_pipe;

	i = -1;
	nb_pipe = 0;
	while (tab[++i])
		if (tab[i]->e_type == TOKEN_PIPE)
			nb_pipe++;
	return (nb_pipe);
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
