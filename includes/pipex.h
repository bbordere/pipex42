/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:26:21 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/05 20:13:05 by bbordere         ###   ########.fr       */
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

void	ft_error(char *str);
void	ft_free(char **tab);
void	ft_exec(char *str, char **env);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_open(char *filename, char mode, int here_doc);

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