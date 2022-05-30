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

void	ft_invalid_files(t_data *data, char **av, int ac)
{
	if (data->in == -1)
	{
		write(2, "pipex: ", 8);
		write(2, av[1], ft_strlen(av[1]));
		write(2, ": No such file or directory\n", 28);
	}
	if (data->out == -1)
	{
		write(2, "pipex: ", 8);
		perror(av[ac - 1]);
	}
	ft_free_data(data);
	exit(EXIT_SUCCESS);
}

int	ft_here_doc(char *limiter)
{
	int		fd;
	char	*line;
	size_t	len;

	len = ft_strlen(limiter);
	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	while (1)
	{
		write(0, "pipex heredoc> ", 15);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, len) && line[len] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	return (ft_open(".heredoc", 'R'));
}
