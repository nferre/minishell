/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:47:35 by nferre            #+#    #+#             */
/*   Updated: 2021/11/15 09:36:04 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	nb_word(char *s, char c)
{
	int	i;
	int	counter;

	counter = 0;
	i = -1;
	while (s[++i])
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			counter++;
	return (counter);
}

int	word_len(char const *s, char c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

void	*free_all(char **tab, int i)
{
	int		j;

	j = 0;
	while (j < i)
		free(tab[j++]);
	free(tab);
	return (NULL);
}

char	**aloc(char *s, char c, char **tab, int len)
{
	int		i;
	int		j;
	int		total_len;

	total_len = len;
	i = -1;
	while (++i < total_len && *s)
	{
		j = 0;
		while (*s == c && *s)
			s++;
		if (*s == '\0')
			break ;
		len = word_len(s, c);
		tab[i] = malloc((len + 1) * sizeof(char));
		if (!tab[i])
			return (free_all(tab, i));
		while (len > j)
			tab[i][j++] = *(s++);
		tab[i][j] = '\0';
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc((nb_word((char *)s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab = aloc((char *)s, c, tab, nb_word((char *)s, c));
	return (tab);
}
