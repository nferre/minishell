/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:03:11 by nferre            #+#    #+#             */
/*   Updated: 2021/11/17 15:01:36 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	*handler_function(void)
{
	printf("\r");
	return (NULL);
}

void	all_buildins(char *str, char **env)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	i += echo(str);
	i += cd(str);
	i += pwd(str, env);
	if (i != 0)
		return ;
	find_exec(str);
}

void	prompt(char *str, char **argv, char **env)
{
	char	*oui = "/usr/bin";
	char	*non = "Makefile";
	while (str != NULL)
	{	
		signal(SIGQUIT, (void *)handler_function);
		signal(SIGINT, (void *)handler_function);
		str = readline("minishell$ ");
		all_buildins(str, env);
		add_history(str);
	}
	printf("\nexit\n");
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;

	str = "oui";
	prompt(str, argv, env);
	return (0);
}
