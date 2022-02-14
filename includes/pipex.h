/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:26:21 by bbordere          #+#    #+#             */
/*   Updated: 2022/02/14 23:32:28 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <string.h>

void	ft_error(char *str);
void	ft_free(char **tab);
char	*ft_path(char *cmd, char **env);
void	ft_exec(char *str, char **env);
int	    ft_open(char *filename, char mode, int here_doc);

#endif