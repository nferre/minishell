/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:26:54 by nferre            #+#    #+#             */
/*   Updated: 2022/01/09 10:32:37 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	get_pos_in_env(char **env, char *str)
{
	int	i;

	i = -1;
	while (env[++i])
		if (strncmp(env[i], str, ft_strlen(str)) == 0)
			return (i);
	return (-1);
}

void	get_old_pwd(char **env, int *ver)
{
	char	cwd[PATH_MAX];
	int		pos_old_pwd;
	
	pos_old_pwd = get_pos_in_env(env, "OLDPWD");
	if (*ver > 0)
		free(env[pos_old_pwd]);
	env[pos_old_pwd] = ft_strjoin("OLDPWD=", getcwd(cwd, sizeof(cwd)));
}

void	get_new_pwd(char **env, int *ver)
{
	char	cwd[PATH_MAX];
	int		pos_pwd;

	pos_pwd = get_pos_in_env(env, "PWD");

	if (*ver > 0)
		free(env[pos_pwd]);
	env[pos_pwd] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	*ver += 1;
}

int	cd(t_token **tab, char **env)
{
	int			i;
	char 		*cd;
	char		*home;
	static int	ver;

	cd = "cd";
	i = -1;
	while (++i != 2)
		if (cd[i] != tab[0]->value[i])
			return (0);
	home = getenv("HOME");
	get_old_pwd(env, &ver);
	if (tab[1] == NULL)
	{
		chdir(home);
		get_new_pwd(env, &ver);
		return (1);
	}
	if (chdir(tab[1]->value) == -1)
		printf("minishell: cd: %s: %s\n", tab[1]->value, strerror(errno));
	else
		get_new_pwd(env, &ver);
	return (1);
}
