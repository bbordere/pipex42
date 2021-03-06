/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:26:21 by bbordere          #+#    #+#             */
/*   Updated: 2022/04/23 18:23:27 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define BUFFER_SIZE 1

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>

typedef struct s_data
{
	int		nb_cmd;
	int		in;
	int		out;
	int		here_doc;
	char	**cmds;
	int		**pipes;
	pid_t	*childs;

}	t_data;

t_data	*ft_init_data(int ac, char **av);

void	*ft_free(char **tab);
void	ft_close(int fd1, int fd2);
void	ft_free_data(t_data *data);
void	ft_error(char *str, int mode);
void	ft_exec_last(t_data *data, char **env);
void	ft_exec_first(t_data *data, char **env);
void	ft_invalid_files(t_data *data, char **av, int ac);
void	ft_exec(char *str, char **env, t_data *data);

int		ft_wait_all(t_data *data);
int		ft_here_doc(char *limiter);
int		ft_open(char *filename, char mode);
int		ft_pipeline(t_data *data, char **env);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*get_next_line(int fd);
char	*ft_strdup(const char *source);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_path(char *cmd, char **env);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);

size_t	ft_strlen(const char *str);

#endif