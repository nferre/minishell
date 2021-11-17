/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:03:53 by nferre            #+#    #+#             */
/*   Updated: 2021/11/17 15:03:40 by nferre           ###   ########.fr       */
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

char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	all_builtins(char *s, char **env);
int		echo(char *str);
int		cd(char	*s);
int		pwd(char *s, char **env);
void	prompt(char *str, char **argv, char **env);
void	*handler_function(void);
char	**ft_split(char const *s, char c);
void	find_exec(char *str);
#endif
