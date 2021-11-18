/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:03:11 by nferre            #+#    #+#             */
/*   Updated: 2021/11/18 09:51:14 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	*handler_function(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		printf("\nminishell$ ");
	}
	if (sig == SIGQUIT)
	{
		rl_redisplay();
		printf("minishell$   \b\b");
	}
	return (NULL);
}

void	all_buildins(char *str, char **env)
{
	int	i;

	i = 0;
	(void)env;
	if (str == NULL)
		return ;
	i += echo(str);
	i += cd(str);
	i += pwd(str);
	if (i != 0)
		return ;
	find_exec(str);
}

void	prompt(char *str, char **env)
{
	while (str != NULL)
	{	
		signal(SIGQUIT, (void *)handler_function);
		signal(SIGINT, (void *)handler_function);
		str = readline("minishell$ ");
		all_buildins(str, env);
		add_history(str);
	}
	printf("exit\n");
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	
	(void)argc;
	(void)argv;
	str = "oui";
	prompt(str, env);
	return (0);
}
