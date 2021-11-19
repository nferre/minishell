/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:03:11 by nferre            #+#    #+#             */
/*   Updated: 2021/11/19 09:39:50 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

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
	char	*to_print;

	i = 0;
	(void)env;
	if (str == NULL)
		return ;
	if (str[0] == '\0')
		return ;
	while (str[i])
	{
		if (str[i] < 27 || str[i] > 127)
			return ;
		i++;
	}
	i = 0;
	to_print = echo(str, &i);
	i += cd(str);
	i += pwd(str);
	exit_all(str);
	if (i != 0)
		return ;
	while (str[i] == ' ')
	{
		if (str[i] == ' ' && str[i + 1] == '\0')
			return ;
		i++;
	}
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
	printf("\b\bexit\n");
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;

	(void)argc;
	(void)argv;
	str = "\0";
	prompt(str, env);
	return (0);
}
