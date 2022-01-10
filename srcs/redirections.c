/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:05:52 by nferre            #+#    #+#             */
/*   Updated: 2022/01/09 15:40:19 by nferre           ###   ########.fr       */
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
	while (tab[i]->e_type == 0 || tab[i]->e_type == 7 || tab[i]->e_type == 8)
	{
		i++;
		if (tab[i] == NULL)
		{
			*check = 1;
			break ;
		}
	}
	new = malloc(sizeof(t_token *) * (i + 1));
	while (tab[j]->e_type == 0 || tab[i]->e_type == 7 || tab[i]->e_type == 8)
	{
		new[k] = malloc(sizeof(t_token));
		new[k]->e_type = tab[j]->e_type;
		new[k]->value = ft_strdup(tab[j]->value);
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
	int	i;

	i = 0;
	check = 0;
	while (check != 1)
	{
		if (i != 0)
			free(new);
		new = get_new_tab(tab, ver, &check);
		create_file(str, new[0]->value, check_redirect(tab));
		i++;
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
