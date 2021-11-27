/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:55:45 by hadufer           #+#    #+#             */
/*   Updated: 2021/11/27 18:13:58 by hadufer          ###   ########.fr       */
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
# include <termios.h>

char	**add_elem_env(char **env, char *data, char *data_name);
int		verify(char *str);
int		export_var(char *str, char **env);
int		set(char *str);
void	rl_replace_line(const char *str, int i);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	all_builtins(char *s, char **env);
char	*echo(char *str, int *i);
int		cd(char	*s);
int		pwd(char *s);
void	prompt(char *str, char **env);
void	*handler_function(int sig);
char	**ft_split(char const *s, char c);
void	find_exec(char *str, char **env);
void	exit_all(char *str);
int		show_env(char *str, char **env);
// UTILS
int		ft_isspace(int c);
char	*ft_strndup(char *str, int n);
size_t	ft_strlen_null(char *s);
char	*ft_strjoin_null(char *s1, char *s2);
#endif
