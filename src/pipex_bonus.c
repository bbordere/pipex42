/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:42:45 by bbordere          #+#    #+#             */
/*   Updated: 2022/04/23 18:48:31 by bbordere         ###   ########.fr       */
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

void	ft_child(char *cmd, char **env, int in, int mode)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
	{
		dup2(fd[1], STDOUT_FILENO);
		if (in == STDIN_FILENO)
			exit(EXIT_FAILURE);
		ft_exec(cmd, env);
		ft_close(fd[0], fd[1]);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		ft_close(fd[0], fd[1]);
		if (mode)
			waitpid(pid, NULL, 0);
	}
	if (in != STDOUT_FILENO)
		close(in);
}

int	main(int ac, char **av, char **env)
{
	int	in;
	int	out;
	int	i;

	if (!env || !*env || ac < 5)
		exit(EXIT_FAILURE);
	i = 2;
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
	{
		in = ft_here_doc(av[i++]);
		out = ft_open(av[ac - 1], 'A');
	}
	else
	{
		in = ft_open(av[1], 'R');
		out = ft_open(av[ac - 1], 'T');
	}
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	ft_close(in, out);
	ft_child(av[i], env, in, 0);
	while (++i < ac - 2)
		ft_child(av[i], env, STDOUT_FILENO, 1);
	ft_exec(av[i], env);
	return (1);
}
