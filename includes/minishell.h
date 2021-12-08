/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:55:45 by hadufer           #+#    #+#             */
/*   Updated: 2021/12/08 13:35:33 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "token.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <limits.h>
# include <fcntl.h>

char	**get_arg(t_token **tab);
char	*get_local_var(char **env, char *str);
void	redirect_output(char *str, t_token **tab, int *ver);
int		check_redirect(t_token **tab);
void	create_file(char *str, char *name, int check);
int		get_nb_red(t_token **tab);
t_token	**get_new_tab(t_token **tab, int *ver, int *check);
int		ft_strncmp(const char *s1, const char *s2, unsigned int i);
size_t	ft_strlen(const char *s);
char	**add_elem_env(char **env, char *data, char *data_name);
int		verify(t_token **tab);
int		export_var(t_token **tab, char **env);
int		set(char *str);
void	rl_replace_line(const char *str, int i);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	all_builtins(t_token **tab, char **env, char *str);
char	*echo(t_token **tab, int *i);
int		cd(t_token **tab);
char	*pwd(t_token **tab, int *i, char *to_print);
void	prompt(char *str, char **env);
void	*handler_function(int sig);
char	**ft_split(char const *s, char c);
void	find_exec(t_token **new, char **env, t_token **tab);
void	exit_all(t_token **tab);
char	*show_env(t_token **tab, char **env, int *j, char *to_print);
// UTILS
char	*ft_strjoin_free(char *s1, char const *s2);
int		ft_isspace(int c);
char	*ft_strndup(char *str, int n);
size_t	ft_strlen_null(char *s);
char	*ft_strjoin_null(char *s1, char *s2);
#endif
