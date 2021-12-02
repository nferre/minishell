/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:03:11 by nferre            #+#    #+#             */
/*   Updated: 2021/12/02 10:36:08 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "lexer.h"
#include "libft.h"
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
		printf("minishell$ ");
	}
	return (NULL);
}

void	all_builtins(t_token **tab, char **env, char *str)
{
	int	i;
	t_token	**new;
	char	*to_print;
	int ver;
	int	check;

	check = 0;
	ver = 0;
	i = 0;
	if (tab[0]->value[0] == '\0')
		return ;
	i = 0;
	if (check_redirect(tab) != 0)
	{
		new = malloc(sizeof(t_token *));
		free(new);
		new = get_new_tab(tab, &ver, &check);
	}
	else
		new = tab;
	to_print = echo(new, &i);
	to_print = show_env(new, env, &i, to_print);
	i += cd(new);
	to_print = pwd(new, &i, to_print);
	i += export_var(new, env);
	exit_all(new);
	if (check_redirect(tab) != 0)
		redirect_output(to_print, tab, &ver);
	else if (to_print != NULL)
		printf("%s", to_print);
	free(to_print);
	free(new);
	if (i != 0)
		return ;
	find_exec(str, env);
}

t_token		**get_tab(char *str)
{
	t_token	*token;
	t_lexer	*lexer;
	t_token	**tab;
	int	size_tab;
	int	i;

	i = 0;
	size_tab = 1;
	lexer = init_lexer(str);
	while (lexer->c)
	{
		size_tab++;
		token = lexer_get_next_token(lexer);
		free(token);
	}
	free(lexer);
	tab = malloc(sizeof(t_token *) * size_tab);
	lexer = init_lexer(str);
	while (lexer->c)
	{
		token = lexer_get_next_token(lexer);
		tab[i] = token;
		i++;
	}
	free(lexer);
	tab[i] = NULL;
	return (tab);
}

void	prompt(char *str, char **env)
{
	struct termios *term;
	t_token	**tab;

	term = malloc(sizeof(struct termios));
	tcgetattr(0, term);
	term->c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW,term);
	while (str != NULL)
	{
		free(str);
		signal(SIGQUIT, (void *)handler_function);
		signal(SIGINT, (void *)handler_function);
		str = readline("minishell$ ");
		if (str == NULL)
			break ;
		add_history(str);
		tab = get_tab(str);
		all_builtins(tab, env, str);
	}
	printf("exit\n");
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;

	(void)argc;
	(void)argv;
	str = "\0";
	str = malloc(sizeof(char));
	prompt(str, env);
	return (0);
}
