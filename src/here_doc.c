/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:49:58 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/14 14:49:58 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_get_doc(char *limiter, int *fd)
{
	char	*line;
	size_t	len;

	close(fd[0]);
	len = ft_strlen(limiter);
	while (1)
	{
		write(0, "pipex heredoc> ", 15);
		line = get_next_line(0);
		if (!line)
			break ;
		if (line[len] == '\n' && !ft_strncmp(line, limiter, len))
		{
			free(line);
			close(fd[1]);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
}

int	ft_here_doc(char *limiter)
{
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		ft_error("fork", 0);
	if (pid == 0)
	{
		close(fd[0]);
		ft_get_doc(limiter, fd);
	}
	else
	{
		close(fd[1]);
		wait(NULL);
	}
	return (fd[0]);
}
