/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:03:11 by nferre            #+#    #+#             */
/*   Updated: 2022/01/05 22:43:04 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "lexer.h"
#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <fcntl.h>

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

void	free_arg(char **arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		free(arg[i]);
	free(arg);
}

void	rm(char **env, t_token **new)
{
	char **arg;

	if (access(".HlPusER9jae3ffz5sDJu!=05", X_OK) != -1)
	{

		new[0]->value = ft_strdup(".HlPusER9jae3ffz5sDJu!=05");
		arg = get_arg(new);
		if (fork() != 0)
		{
			free(new[0]->value);
			free_arg(arg);
			wait(NULL);
			return ;
		}
		execve("/bin/rm", arg, env);
	}
}

void	free_tab(t_token **tab)
{
	int	i;

	i = -1;
	if (tab == NULL)
		return ;
	while (tab[++i])
	{
		if (!(tab[i]))
			break  ;
		free(tab[i]->value);
		if (tab[i])
			free(tab[i]);
	}
	free(tab);
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
	i = 0;
	if (check_redirect(tab) != 0)
	{
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
	if (check_redirect(tab) != 0 && i > 0)
		redirect_output(to_print, tab, &ver);
	else if (to_print != NULL)
		printf("%s", to_print);
	free(to_print);
	if (i != 0)
	{
		return ;
	}
	find_exec(new, env, tab);
	rm(env, new);
	free_tab(new);
}

char	*heredoc(char *str_stop)
{
	char 	*temp;
	int	fd;

	fd = open(".HlPusER9jae3ffz5sDJu!=05", O_WRONLY | O_CREAT, S_IRWXU | O_TRUNC);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	printf("\n");
	temp = malloc(sizeof(char));
	temp[0] = '\0';
	while (ft_strncmp(temp, str_stop, ft_strlen(str_stop)))
	{
		free(temp);
		temp = readline("> ");
		ft_putendl_fd(temp, fd);
	}
	free(temp);
	close(fd);
	free(str_stop);
	return (".HlPusER9jae3ffz5sDJu!=05");
}

t_token		**get_tab(char *str, char **env)
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
		token = lexer_get_next_token(lexer);
		if (token->e_type == 2)
			continue ;
		destroy_token(token);
		size_tab++;
	}
	free(lexer);
	tab = malloc(sizeof(t_token *) * size_tab);
	lexer = init_lexer(str);
	while (lexer->c)
	{
		token = lexer_get_next_token(lexer);
		if (token->e_type == 2)
			continue ;
		else if (token->e_type == 3)
		{
			destroy_token(token);
			token = lexer_get_next_token(lexer);
			token->value = heredoc(token->value);
		}
		else if (token->value[0] == '$')
			token->value = get_local_var(env, token->value + 1);
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
	char	*str_joined;
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
		str = readline("minishell$> ");
		if (str == NULL)
			break ;
		else if (str[0] == '\0')
			continue ;
		add_history(str);
		tab = get_tab(str, env);
		all_builtins(tab, env, str);
		free_tab(tab);
	}
	free(str);
	printf("exit\n");
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;

	(void)argc;
	(void)argv;
	init_global_data(env);
	str = "\0";
	str = malloc(sizeof(char));
	prompt(str, env);
	// t_lexer *test = init_lexer("echo $a");
	// t_token *t = lexer_get_next_token(test);
	// t = expand_token(t);
	// while (t)
	// {
	// 	printf("%d : %s\n", t->e_type, t->value);
	// 	t = lexer_get_next_token(test);
	// 	t = expand_token(t);
	// }
	return (0);
}
