/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:03:53 by nferre            #+#    #+#             */
/*   Updated: 2021/11/19 10:15:01 by nferre           ###   ########.fr       */
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
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	all_builtins(char *s, char **env);
char	*echo(char *str, int	*i);
int		cd(char	*s);
int		pwd(char *s);
void	prompt(char *str, char **env);
void	*handler_function(int sig);
char	**ft_split(char const *s, char c);
void	find_exec(char *str, char **env);
void	exit_all(char *str);
int		show_env(char *str, char **env);
#endif
