/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:05:52 by nferre            #+#    #+#             */
/*   Updated: 2021/12/02 10:43:56 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	get_nb_red(t_token **tab)
{
	int	i;
	int	nb_red;

	nb_red = 0;
	i = -1;
	while (tab[++i])
		if (tab[i]->e_type != 0)
			nb_red++;
	return (nb_red);
}

t_token **get_size(t_token **tab, int *ver, int *check)
{
	static int	i;
	int	j;
	int	k;
	t_token **new;

	k = 0;
	if (*ver == 0)
		i = 0;
	j = i;
	while (tab[i]->e_type == 0)
	{
		i++;
		if (tab[i] == NULL)
		{
			*check = 1;
			break ;
		}
	}
	new = malloc(sizeof(t_token *) * (i + 1));
	while (tab[j]->e_type == 0)
	{
		new[k] = tab[j];
		k++;
		j++;
		if (tab[j] == NULL)
			break ;
	}
	new[k] = NULL;
	*ver += 1;
	i++;
	return (new);
}

void	create_file(char *str, char *name, int check)
{
	static int	fd;
	static char *last_name;
	int	i;

	i = -1;
	if (fd == 0)
		last_name = ft_strdup(name);
	else
	{
		fd = open(last_name, O_WRONLY | O_TRUNC);
		close(fd);
	}
	if (check == 1)
		fd = open(name, O_WRONLY | O_CREAT, S_IRWXU | O_TRUNC);
	else if (check == 4)
	{
		fd = open(name, O_WRONLY | O_APPEND, S_IRWXU | O_CREAT);
		if (fd == -1)
			fd = open(name, O_WRONLY | O_CREAT, S_IRWXU | O_TRUNC);
	}
	while (str[++i])
		write(fd, &str[i], 1);
	close(fd);
	free(last_name);
	last_name = ft_strdup(name);
}

t_token **get_new_tab(t_token **tab, int *ver, int *check)
{
	return (get_size(tab, ver, check));
}

void	redirect_output(char *str, t_token **tab, int *ver)
{
	t_token	**new;
	int	check;

	check = 0;
	while (check != 1)
	{
		new = get_new_tab(tab, ver, &check);
		create_file(str, new[0]->value, check_redirect(tab));
	}
}

int	check_redirect(t_token **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if (tab[i]->e_type == 1)
			return (1);
		else if (tab[i]->e_type == 4)
			return (4);
	}
	return (0);	
}
