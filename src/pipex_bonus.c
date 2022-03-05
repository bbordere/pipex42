/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:42:45 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/05 20:35:17 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_get_doc(char *limiter, int *fd)
{
	char	*line;

	while (1)
	{
		write(1, "pipex heredoc> ", 15);
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
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
		ft_error("fork");
	if (pid == 0)
	{
		close(fd[0]);
		ft_get_doc(limiter, fd);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
	}
	return (fd[0]);
}

void	ft_child(char *cmd, char **env, int in)
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
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (in == STDIN_FILENO)
			exit(EXIT_FAILURE);
		ft_exec(cmd, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	ft_check_open(char *filename)
{
	int	in;

	in = ft_open(filename, 'R', 0);
	if (in == -1)
		ft_error(filename);
	dup2(in, STDIN_FILENO);
	close(in);
}

int	main(int ac, char **av, char **env)
{
	int	in;
	int	out;
	int	i;

	if (!env || ac < 5)
		exit(EXIT_FAILURE);
	i = 2;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		in = ft_here_doc(av[2]);
		out = ft_open(av[ac - 1], 'A', 0);
		i++;
	}
	else
	{
		in = ft_open(av[1], 'R', 1);
		out = ft_open(av[ac - 1], 'T', 0);
	}		
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	ft_child(av[i], env, in);
	while (++i < ac - 2)
		ft_child(av[i], env, STDOUT_FILENO);
	ft_exec(av[i], env);
	return (1);
}
