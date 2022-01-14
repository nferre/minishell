/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:49:49 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/14 13:55:12 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <fcntl.h>

void	*handler_function(int sig)
{
	//permet de gerer les signaux
	if (sig == SIGINT)
	{
		if (g_data.exec == 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			printf("\nminishell$> ");
		}
		else
			printf("\n");
	}
	if (sig == SIGQUIT)
	{
		if (g_data.exec == 0)
		{
			rl_on_new_line();
			rl_redisplay();
		}
		else
			printf("Quit: 3\n");
	}
	return (NULL);
}

void	free_tab(t_token **tab)
{
	//free 'tab' (tableau avec tous les tokens) dans prompt et 'new' dans all_builtins
	int	i;

	i = -1;
	if (tab == NULL)
		return ;
	while (tab[++i])
	{
		free(tab[i]->value);
		if (tab[i])
			free(tab[i]);
	}
	free(tab);
}

void	all_builtins(t_token **tab, char **env)
{
	int	i;
	int ver;
	int	check;
	int	i_to_exec;

	check = 0;
	ver = 0;
	i = 0;
	i_to_exec = get_first_operand_index(tab, 0);
	if (tab[0]->value[0] == '\0')
	{
		printf("minishell : : command not found\n");
		return ;
	}
	if (count_operand(tab, 0) > 1)
		stdout_stdin_pipe();
	while (i_to_exec > -1)
	{
		if (tab[i_to_exec]->e_type == TOKEN_PIPE)
			pipe_exec(tab, i_to_exec);
		else if (tab[i_to_exec]->e_type == TOKEN_REDIRECT_OUT_APPEND)
		 	redirect_out_append_exec(tab, i_to_exec);
		else if (tab[i_to_exec]->e_type == TOKEN_REDIRECT_OUT)
			redirect_out_exec(tab, i_to_exec);
		else if (tab[i_to_exec]->e_type == TOKEN_REDIRECT_IN_HEREDOC)
			redirect_in_heredoc_exec(tab, i_to_exec);
		else if (tab[i_to_exec]->e_type == TOKEN_REDIRECT_IN)
			redirect_in_exec(tab, i_to_exec);
		i_to_exec = get_first_operand_index(tab, i_to_exec + 1);
	}
	g_data.more_than_one_operand = 0;
	if (g_data.create_file == 1)
		g_data.create_file = 0;
	if (count_operand(tab, 0) == 0)
	{
		i_to_exec = 0;
		exit_all(tab);
		if (check_exec_builtins(tab, i_to_exec) == 0)
			find_exec(env, tab, 0);
	}
}

t_token		**get_tab(char *str)
{
	//creer le tableau dans lequel tous les token sont stocke
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
		destroy_token(token);
		size_tab++;
	}
	free(lexer);
	tab = malloc(sizeof(t_token *) * size_tab);
	lexer = init_lexer(str);
	while (lexer->c)
	{
		token = lexer_get_next_token(lexer);
		token = expand_token(token);
		if (token->e_type == 7 || token->e_type == 8)
			token->e_type = 0;
		tab[i] = token;
		i++;
	}
	free(lexer);
	tab[i] = NULL;
	return (tab);
}

void	prompt(char *str, char **env)
{
/*
gere les signaux ──────► recupere l'input ────────► l'ajoute la commande
                         utilisatueur               a l'historique
                                                           │
                                                           │
                                                           ▼
                                                    creer le tableau
                     execute la commande ◄────────  de token
*/
	t_token	**tab;

	g_data.term = malloc(sizeof(struct termios));
	tcgetattr(0, g_data.term);
	g_data.term->c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, g_data.term);
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
		else if (is_empty(str) == 0)
		{
			add_history(str);
			continue ;
		}
		add_history(str);
		tab = get_tab(str);
		if (verify_redirect(tab) == 1)
		{
			free_tab(tab);
			continue ;
		}
		all_builtins(tab, env);
		free_tab(tab);
		g_data.check_rm = 0;
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
	// t_lexer *test = init_lexer(ft_strdup("echo \"l\"ad"));
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
