/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 16:43:23 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/15 17:12:30 by hadufer          ###   ########.fr       */
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

void	get_tab_util(t_lexer **lexer, t_token **t, t_token ***tab, char *str)
{
	int		size_tab;

	size_tab = 1;
	*lexer = init_lexer(str);
	while ((*lexer)->c)
	{
		*t = lexer_get_next_token(*lexer);
		if (!*t)
			break ;
		destroy_token(*t);
		size_tab++;
	}
	free(*lexer);
	*tab = malloc(sizeof(t_token *) * size_tab);
}

t_token	**get_tab(char *str)
{
	t_token	*token;
	t_lexer	*lexer;
	t_token	**tab;
	int		i;

	tab = NULL;
	token = NULL;
	lexer = NULL;
	get_tab_util(&lexer, &token, &tab, str);
	i = 0;
	lexer = init_lexer(str);
	while (lexer->c)
	{
		token = lexer_get_next_token(lexer);
		if (!token)
			break ;
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

void	prompt_builtins(t_token **tab, char **env)
{
	all_builtins(tab, env);
	free_tab(tab);
	g_data.check_rm = 0;
}

void	prompt_util_while(t_token ***tab, char **env, char **str)
{
	while (*str != NULL)
	{
		free(*str);
		signal(SIGQUIT, (void *)handler_function);
		signal(SIGINT, (void *)handler_function);
		*str = readline("minishell$> ");
		if (*str == NULL)
			break ;
		else if ((*str)[0] == '\0')
			continue ;
		else if (is_empty(*str) == 0)
		{
			add_history(*str);
			continue ;
		}
		add_history(*str);
		*tab = get_tab(*str);
		if (verify_redirect(*tab) == 1)
		{
			free_tab(*tab);
			continue ;
		}
		prompt_builtins(*tab, env);
	}
}

void	prompt(char *str, char **env)
{
	t_token	**tab;

	g_data.term = malloc(sizeof(struct termios));
	tcgetattr(0, g_data.term);
	g_data.term->c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, g_data.term);
	prompt_util_while(&tab, env, &str);
	free(str);
	printf("exit\n");
	exit(0);
}
