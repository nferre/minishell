/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:03:53 by nferre            #+#    #+#             */
/*   Updated: 2021/11/25 09:50:49 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

void	rl_replace_line(const char *str, int i);
void	all_builtins(char *s, char **env);
// BUILTINS
int		echo(char *str);
int		cd(char	*s);
int		pwd(char *s);
void	prompt(char *str, char **env);
void	*handler_function(int sig);
char	**ft_split(char const *s, char c);
void	find_exec(char *str);
// UTILS
int		ft_isspace(int c);
int	 	ft_strcmp(const char *s1, const char *s2);
#endif
