/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:55:45 by hadufer           #+#    #+#             */
/*   Updated: 2022/01/15 16:49:41 by hadufer          ###   ########.fr       */
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
# include <errno.h>
# include <string.h>

typedef struct	s_data
{
	char	**env;
	int		last_exit_status;
	int		exec;
	int		check_rm;
	struct	termios *term;
	int		more_than_one_operand;
	int		fd_base_stdin;
	int		fd_base_stdout;
	int		fd_operand_pipe[2];
	int		create_file;
}				t_data;

typedef enum
{
	NOT_FOUND,
	ECH0,
	CD,
	ENV,
	PWD,
	UNSET,
	EXPORT
}	e_return_type_builtins;

t_data	g_data;

int		check_arg(t_token **tab, int i_to_exec);
int		check_export(t_token **tab, int i_to_exec);
char	**get_arg(t_token **tab, int i_to_exec);
char	*get_local_var(char **env, char *str);
void	redirect_output(char *str, t_token **tab, int *ver);
int		check_redirect(t_token **tab);
void	create_file(char *str, char *name, int check);
int		get_nb_red(t_token **tab);
t_token	**get_new_tab(t_token **tab, int *ver, int *check);
int		ft_strncmp(const char *s1, const char *s2, unsigned int i);
size_t	ft_strlen(const char *s);
char	**add_elem_env(char **env, char *data, char *data_name);
int		verify(t_token **tab, int i_to_exec);
int		export_var(t_token **tab, char **env, int i_to_exec);
void	rl_replace_line(const char *str, int i);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	all_builtins(t_token **tab, char **env);
int		echo(t_token **tab, int i_to_exec);
int		cd(t_token **tab, char **env, int i_to_exec);
int		pwd(t_token **tab, int i_to_exec);
void	prompt(char *str, char **env);
void	*handler_function(int sig);
char	**ft_split(char const *s, char c);
void	find_exec(char **env, t_token **tab, int i_to_exec);
void	exit_all(t_token **tab);
void	del_elem_env(char **env, char *data_name);
int		show_env(t_token **tab, char **env, int i_to_exec);
int		get_line_local_var(char **env, char *data_name);
int		unset(t_token **tab, char **env, int i_to_exec);
char	*get_name(t_token **tab, int i_to_exec);
int		verify_redirect(t_token **tab);
int		pipe_exec(t_token **tab, int i_to_exec);
int		check_exec_builtins(t_token **tab, int i_to_exec);
int		redirect_in_exec(t_token **tab, int i_to_exec);
void	redirect_out_exec(t_token **tab, int i_to_exec);
void	redirect_out_append_exec(t_token **tab, int i_to_exec);
int		redirect_in_heredoc_exec(t_token **tab, int i_to_exec);
char	*ft_getenv(char *str);
// UTILS
t_token	**dup_double_token_array(t_token **tab);
char	*ft_strjoin_free(char *s1, char const *s2);
char	*ft_strjoin_free_null(char *s1, char const *s2);
int		ft_isspace(int c);
char	*ft_strndup(char *str, int n);
size_t	ft_strlen_null(char *s);
char	*ft_strjoin_null(char *s1, char *s2);
char	*ft_remchar(char *str, size_t i);
char	*ft_remstring(char *str, int i, int j);
char	*ft_insert_string(char *haystack, char *needle, int k);
void	init_global_data(char **env);
int		is_empty(char *str);
int		get_first_operand_index(t_token **tab, int i_to_exec);
int		get_tab_length(t_token **tab);
int		count_operand(t_token **tab, int i_to_exec);
void	stdout_stdin_pipe(void);
void	redirect_stdout_stdin_pipe(void);
void	redirect_stdin_pipe(void);
void	redirect_stdout_pipe(void);
int		is_last_operand(t_token **tab, int i_to_exec);
int		is_first_operand(t_token **tab, int i_to_exec);
int		get_previous_operand_index(t_token **tab, int i_to_exec);
int		get_nb_pipe_operand(t_token **tab);
void	print_in_fd(void);
void	free_tab(t_token **tab);
#endif
